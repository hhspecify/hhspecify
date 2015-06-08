<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\reporter;

use specify\LifeCycleEvent;
use specify\LifeCycleMessageSubscriber;
use specify\event\FeaturePackageStart;
use specify\event\FeaturePackageFinish;
use specify\io\ConsoleOutput;
use specify\io\Console;


final class ProcessingTimeReporter implements LifeCycleMessageSubscriber
{

    public function __construct(
        private Console $writer = new ConsoleOutput()
    )
    {
    }

    public function receive(LifeCycleEvent $event) : void
    {
        if ($event instanceof FeaturePackageFinish) {
            $this->onPackageFinish($event);
        }
    }

    private function onPackageFinish(FeaturePackageFinish $event) : void
    {
        $processingTime = $event->getProcessingTime();
        $this->writer->write("Finished in %F seconds\n", $processingTime);
    }

}
