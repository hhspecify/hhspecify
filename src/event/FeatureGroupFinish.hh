<?hh //strict

/**
 * This file is part of hhspecify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhspecify\event;

use hhspecify\LifeCycleEvent;
use hhspecify\LifeCycleEventType;
use hhspecify\result\FeatureGroupResult;
use DateTime;

final class FeatureGroupFinish extends AbstractNamedEvent implements LifeCycleEvent
{

    public function __construct(
        private FeatureGroupResult $result
    )
    {
        parent::__construct(LifeCycleEventType::ExampleGroupFinish);
    }

    public function getFeatureCount() : int
    {
        return $this->result->getFeatureCount();
    }

    public function getFailedFeatureCount() : int
    {
        return $this->result->getFailedFeatureCount();
    }

    public function getLabelGroupFeatureResults() : LabelGroupFeatureResult
    {
        return $this->result->getLabelGroupFeatureResults();
    }

    public function getProcessingTime() : float
    {
        $processingTime = $this->result->getProcessingTime();
        return $processingTime->getProcessingTime();
    }

    public function isPassed() : bool
    {
        return $this->result->isPassed();
    }

    public function isFailed() : bool
    {
        return $this->result->isFailed();
    }

    public function isPending() : bool
    {
        return $this->result->isPending();
    }

    public function getFeatureGroupResult() : FeatureGroupResult
    {
        return $this->result;
    }

}
