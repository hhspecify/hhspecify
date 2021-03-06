<?hh //strict

/**
 * This file is part of hhspecify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhspecify\feature;

use hhspecify\FeatureSpecification;
use hhspecify\notifier\FeaturePackageNotifier;
use hhspecify\result\FeaturePackageResult;
use hhspecify\util\StopWatch;


class FeaturePackage implements FeatureSpecification<FeaturePackageResult, FeaturePackageNotifier>
{

    private StopWatch $stopWatch;

    public function __construct(
        private string $description,
        private FeatureGroupCollection $featureGroups
    )
    {
        $this->stopWatch = new StopWatch();
    }

    public function getDescription() : string
    {
        return $this->description;
    }

    public function verify(FeaturePackageNotifier $notifier) : FeaturePackageResult
    {
        $results = Vector {};
        $notifier->featurePackageStart($this->getDescription());

        $this->stopWatch->start();

        foreach ($this->featureGroups as $featureGroup) {
            $result = $featureGroup->verify($notifier);
            $results->add($result);
        }

        $this->stopWatch->stop();
        $totalTime = $this->stopWatch->getResult();

        $packageResult = new FeaturePackageResult(
            $this->getDescription(),
            $results->toImmVector(),
            $totalTime
        );

        $notifier->featurePackageFinish($packageResult);

        return $packageResult;
    }

}
