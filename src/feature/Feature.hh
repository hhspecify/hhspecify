<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\feature;

use specify\Specification;
use specify\FeatureSpecification;
use specify\LifeCycleNotifier;
use specify\result\FeatureResult;
use specify\util\StopWatch;
use \ReflectionMethod;
use \Exception;


class Feature implements FeatureSpecification<FeatureResult>
{

    const string ATTRIBUTE_NAME = 'Example';

    private string $description = 'example description empty';
    private StopWatch $stopWatch;

    public function __construct(
        private Specification $target,
        private ReflectionMethod $method
    )
    {
        $this->init();
    }

    public function verify(LifeCycleNotifier $notifier) : FeatureResult
    {
        $notifier->featureStart($this->description);

        $result = $this->verifyExample();

        $notifier->featureFinish($result);

        return $result;
    }

    private function init() : void
    {
        $this->stopWatch = new StopWatch();

        $attributeValues = $this->method->getAttribute(self::ATTRIBUTE_NAME);

        if ($attributeValues === null) {
            return;
        }

        $this->description = (string) $attributeValues[0];
    }

    private function verifyExample() : FeatureResult
    {
        $failedReasonException = null;

        $this->stopWatch->start();
        try {
            $this->method->invoke($this->target);
        } catch (Exception $exception) {
            $failedReasonException = $exception;
        }
        $this->stopWatch->stop();

        $result = null;
        $totalTime = $this->stopWatch->getResult();

        if ($failedReasonException === null) {
            $result = FeatureResult::passed($this->description, $totalTime);
        } else {
            $result = FeatureResult::failed($this->description, $totalTime, $failedReasonException);
        }

        return $result;
    }

}
