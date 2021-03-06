<?hh //strict

/**
 * This file is part of hhspecify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhspecify\collector;

use hhspecify\Collector;
use hhspecify\Specification;
use hhspecify\AttributeType;
use \ReflectionClass;
use \ReflectionMethod;


class MethodCollector implements Collector<Specification, ImmVector<ReflectionMethod>>
{

    public function __construct(
        private AttributeType $attributeType
    )
    {
    }

    public function collectFrom(Specification $target) : ImmVector<ReflectionMethod>
    {
        $results = Vector {};

        $reflection = new ReflectionClass($target);
        $methods = $reflection->getMethods(ReflectionMethod::IS_PUBLIC);

        foreach ($methods as $method) {
            $attributes = new ImmMap($method->getAttributes());
            $attributeType = (string) $this->attributeType;
            if ($attributes->contains($attributeType) == false) {
                continue;
            }
            $results->add($method);
        }

        return $results->toImmVector();
    }

    public static function createForFeature() : MethodCollector
    {
        return new self(AttributeType::Feature);
    }

    public static function createForPendingFeature() : MethodCollector
    {
        return new self(AttributeType::PendingFeature);
    }

}
