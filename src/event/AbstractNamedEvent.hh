<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\event;

use specify\LifeCycleEvent;
use specify\LifeCycleEventType;
use specify\LifeCycleMessageSubscriber;
use \DateTime;


abstract class AbstractNamedEvent implements LifeCycleEvent
{

    private DateTime $sendAtDateTime;
    private float $sendAtMicrotime;

    public function __construct(
        protected LifeCycleEventType $name
    )
    {
        $this->sendAtDateTime = new DateTime();
        $this->sendAtMicrotime = (float) microtime(true);
    }

    public function getName() : string
    {
        return (string) $this->name;
    }

    public function getSendAtDateTime() : DateTime
    {
        return $this->sendAtDateTime;
    }

    public function getSendAtMicrotime() : float
    {
        return $this->sendAtMicrotime;
    }

    public function sendTo(LifeCycleMessageSubscriber $subscriber) : void
    {
        $subscriber->receive($this);
    }

}
