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
use \ReflectionMethod;


class FeatureSpecificationFactory
{

    public function __construct(
        private Specification $target
    )
    {
    }

    public function createFeatureFrom(ReflectionMethod $method) : Feature
    {
        return new Feature($this->target, $method);
    }

    public function createPendingFeatureFrom(ReflectionMethod $method) : PendingFeature
    {
        return new PendingFeature($this->target, $method);
    }

}
