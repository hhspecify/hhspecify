<?hh //partial

use hhspecify\LifeCycleEventType;
use hhspecify\event\FeaturePackageFinish;

describe(FeaturePackageFinish::class, function() {
    describe('->getName()', function() {
        beforeEach(function() {
            $this->message = new FeaturePackageFinish();
        });
        it('returns the event name', function() {
            $name = (string) LifeCycleEventType::ExamplePackageFinish;
            expect($this->message->getName())->toBe($name);
        });
    });
});
