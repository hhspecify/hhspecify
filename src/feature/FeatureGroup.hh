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

use hhspecify\Specification;
use hhspecify\notifier\FeatureGroupNotifier;
use hhspecify\FeatureSpecification;
use hhspecify\result\FeatureGroupResult;
use hhspecify\collector\FeatureCollector;
use hhspecify\util\StopWatch;

use \ReflectionClass;
use \ReflectionMethod;
use \Exception;


class FeatureGroup implements FeatureSpecification<FeatureGroupResult, FeatureGroupNotifier>
{

    private string $description;
    private Specification $featureGroup;
    private FeatureCollection $features;
    private StopWatch $stopWatch;

    public function __construct(
        Specification $target
    )
    {
        $this->description = get_class($target);
        $this->featureGroup = $target;

        $collector = new FeatureCollector();
        $this->features = $collector->collectFrom($this->featureGroup);
        $this->stopWatch = new StopWatch();
    }

    public function getDescription() : string
    {
        return $this->description;
    }

    public function getFeatures() : FeatureCollection
    {
        return $this->features;
    }

    public function verify(FeatureGroupNotifier $notifier) : FeatureGroupResult
    {
        $results = Vector {};

        $notifier->featureGroupStart($this->getDescription());

        $this->stopWatch->start();

        foreach ($this->features as $feature) {
            $result = $feature->verify($notifier);
            $results->add($result);
        }

        $this->stopWatch->stop();
        $totalTime = $this->stopWatch->getResult();

        $result = new FeatureGroupResult(
            $this->description,
            $results->toImmVector(),
            $totalTime
        );

        $notifier->featureGroupFinish($result);

        return $result;
    }

}
