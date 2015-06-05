<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\cli;

use specify\Specify;
use specify\notifier\DefaultLifeCycleNotifier;
use specify\example\ExamplePackage;
use specify\result\ExamplePackageResult;
use specify\collector\ExampleGroupCollector;


class Application
{

    public function run(Argument $argv) : void
    {
        $configFile = $argv->getConfigFile();
        $loadConfigFile = getcwd() . '/' . $configFile;

        include_once $loadConfigFile;

        $config = Specify::currentConfig();

        $lifeCycleNotifier = new DefaultLifeCycleNotifier(ImmVector {
            $config->getExampleReporter()
        });

        $collector = new ExampleGroupCollector();

        $package = $config->getPackage();
        $groups = $collector->collectFrom($package);

        $package = new ExamplePackage($package->getNamespace(), $groups);
        $packageResult = $package->verify($lifeCycleNotifier);

        $this->shutdown($packageResult);
    }

    private function shutdown(ExamplePackageResult $result) : void
    {
        $success = 0;

        if ($result->isFailed()) {
            exit($success);
        }
        exit(1);
    }

}
