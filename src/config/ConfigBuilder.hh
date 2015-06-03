<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\config;

use specify\Config;
use specify\LifeCycleMessageSubscriber;
use specify\specification\PackageSpecification;
use specify\reporter\SpecificationReporter;


class ConfigBuilder
{

    private ?PackageSpecification $package;
    private ExampleReporter $exampleReporter;

    public function __construct()
    {
        $this->exampleReporter = new SpecificationReporter();
    }

    public function package(Package $package) : this
    {
        $this->package = new PackageSpecification($package);
        return $this;
    }

    public function exampleReporter(ExampleReporter $exampleReporter) : this
    {
        $this->exampleReporter = $exampleReporter;
        return $this;
    }

    public function build() : Config
    {
        if ($this->package === null) {
            throw new RequiredException('The package is required');
        }

        return new Config(shape(
            'package' => $this->package,
            'exampleReporter' => $this->exampleReporter
        ));
    }

}
