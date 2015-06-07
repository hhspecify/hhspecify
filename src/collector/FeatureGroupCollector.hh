<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\collector;

use specify\Collector;
use specify\Specification;
use specify\feature\FeatureGroup;
use specify\specification\PackageSpecification;
use specify\specification\NotSpecificationFileException;


class FeatureGroupCollector implements Collector<PackageSpecification, FeatureGroupCollection>
{

    /**
     *
     */
    public function collectFrom(PackageSpecification $target) : FeatureGroupCollection
    {
        $exampleGroups = Vector {};
        $targetDirectory = $target->getPackageDirectory();
        $specificationFiles = $this->getSpecificationFiles($targetDirectory);

        foreach ($specificationFiles as $specificationFile) {
            try {
                $reflection = $target->resolve($specificationFile);
            } catch (NotSpecificationFileException $exception) {
                continue;
            }

            $group = new FeatureGroup($reflection);
            $exampleGroups->add($group);
        }
        $exampleGroups->shuffle();

        return $exampleGroups->toImmVector();
    }

    /**
     * @param string $directory
     */
    private function getSpecificationFiles(DirectoryPath $directory) : SpecificationFileCollection
    {
        $collector = new SpecificationFileCollector();
        return $collector->collectFrom($directory);
    }

}
