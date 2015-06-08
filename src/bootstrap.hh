<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify
{
    use specify\feature\Feature;
    use specify\result\FeatureResult;
    use specify\result\FeatureGroupResult;
    use specify\specification\PackageSpecification;

    use \ReflectionMethod;
    use \Generator;

    type LifeCycleMessageSubscriberCollection = ImmVector<LifeCycleMessageSubscriber>;

    type ExampleCollection = Generator<int, Feature, void>;
    type VerifyResultCollection = Vector<VerifyResult>;
    type ExampleResultCollection = Vector<FeatureResult>; //

    type FeatureReporter = LifeCycleMessageSubscriber;
    type ConfigOptions = shape(
        'package' => PackageSpecification,
        'featureReporter' => FeatureReporter
    );
}

namespace specify\config
{
    use specify\LifeCycleMessageSubscriber;

    type PackageNamespace = string;
    type DirectoryPath = string;

    type SpecificationPackage = shape(
        'namespace' => PackageNamespace,
        'packageDirectory' => DirectoryPath
    );
    type FeatureReporter = LifeCycleMessageSubscriber;
}

namespace specify\result
{
    use specify\result\FeatureResult;

    type FeatureResultCollection = ImmVector<FeatureResult>;
    type FeatureGroupResultCollection = ImmVector<FeatureGroupResult>;
}


namespace specify\collector
{
    use \Generator;
    use specify\FeatureSpecification;
    use specify\feature\Feature;
    use specify\feature\FeatureGroup;
    use specify\notifier\FeatureNotifier;
    use specify\result\FeatureResult;

    type DirectoryPath = string;
    type SpecificationFile = string;
    type SpecificationFileCollection = ImmVector<SpecificationFile>;
    type FeatureCollection = ImmVector<FeatureSpecification<FeatureResult, FeatureNotifier>>;
    type FeatureGroupCollection = ImmVector<FeatureGroup>;
}

namespace specify\feature
{
    use \Generator;
    use specify\FeatureSpecification;
    use specify\result\FeatureResult;
    use specify\notifier\FeatureNotifier;

    type FeatureGroupCollection = ImmVector<FeatureGroup>;
    type FeatureCollection = ImmVector<FeatureSpecification<FeatureResult, FeatureNotifier>>;
}


namespace specify\event
{
    use specify\result\FeatureResult;

    type FeatureResultCollection = ImmVector<FeatureResult>;
}

namespace specify\notifier
{
    use specify\LifeCycleMessageSubscriber;

    type LifeCycleMessageSubscriberCollection = ImmVector<LifeCycleMessageSubscriber>;
}

namespace specify\reporter
{
    use specify\LifeCycleMessageSubscriber;

    type ReporterCollection = ImmVector<LifeCycleMessageSubscriber>;
}

namespace specify\specification
{
    type PackageNamespace = string;
    type DirectoryPath = string;
    type SpecificationFile = string;

    /**
     * <code>
     * $package = shape(
     *     'namespace' => 'vendorname\\spec\\',
     *     'packageDirectory' => '/path/to/'
     * );
     * </code>
     */
    type SpecificationPackage = shape(
        'namespace' => PackageNamespace,
        'packageDirectory' => DirectoryPath
    );
}
