<?hh //strict

/**
 * This file is part of hhspecify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhspecify\config;

use hhspecify\Config;
use hhspecify\Builder;
use hhspecify\LifeCycleMessageSubscriber;
use hhspecify\specification\PackageSpecification;
use hhspecify\reporter\SpecificationReporter;
use hhspecify\reporter\FailedSummaryReporter;
use hhspecify\reporter\CompositionReporter;


class ConfigBuilder implements Builder<Config>
{

    private ?PackageSpecification $package;
    private FeatureReporter $featureReporter;
    private FeatureReporter $summaryReporter;

    public function __construct()
    {
        $this->featureReporter = new SpecificationReporter();
        $this->summaryReporter = new FailedSummaryReporter();
    }

    public function package(SpecificationPackage $package) : this
    {
        $this->package = new PackageSpecification($package);
        return $this;
    }

    public function featureReporter(FeatureReporter $featureReporter) : this
    {
        $this->featureReporter = $featureReporter;
        return $this;
    }

    public function build() : Config
    {

        if ($this->package === null) {
            throw new RequiredException('The package is required');
        }

        $package = $this->package;
        $reporter = new CompositionReporter(ImmVector {
            $this->featureReporter,
            $this->summaryReporter
        });

        return new Config(shape(
            'package' => $package,
            'featureReporter' => $reporter
        ));
    }

}
