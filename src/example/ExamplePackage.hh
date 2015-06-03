<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\example;

use specify\SpecificationExample;
use specify\LifeCycleNotifier;
use specify\result\ExamplePackageResult;


class ExamplePackage implements SpecificationExample<ExamplePackageResult>
{

    public function __construct(
        private string $description,
        private ExampleGroupCollection $exampleGroups
    )
    {
    }

    public function getDescription() : string
    {
        return $this->description;
    }

    public function verify(LifeCycleNotifier $notifier) : ExamplePackageResult
    {
        $groupResults = Vector {};
        $notifier->examplePackageStart($this->getDescription());

        foreach ($this->exampleGroups as $exampleGroup) {
            $result = $exampleGroup->verify($notifier);
            $groupResults->add($result);
        }

        $packageResult = new ExamplePackageResult($this->getDescription(), $groupResults);
        $notifier->examplePackageFinish($packageResult);

        return $packageResult;
    }

}
