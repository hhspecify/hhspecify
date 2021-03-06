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
use \Generator;

class SpecificationFileCollector implements Collector<DirectoryPath, SpecificationFileCollection>
{

    public function collectFrom(DirectoryPath $target) : SpecificationFileCollection
    {
        $specFiles = Vector {};
        $files = $this->findFiles($target);

        foreach ($files as $file) {
            if ($this->matchFile($file) === false) {
                continue;
            }
            $specFiles->add($file);
        }

        return $specFiles->toImmVector();
    }

    private function matchFile(string $entry) : bool
    {
        if (preg_match('/^.+\.hh$/', $entry) === 0) {
            return false;
        }
        return true;
    }

    private function matchDirectory(string $entry) : bool
    {
        if ($entry === ".." || $entry === ".") {
            return false;
        }
        return true;
    }

    private function findFiles(string $target) : Generator<int, SpecificationFile, void>
    {
        $targetDirectory = dir($target);
        $currentDirectory = $target;

        while (false !== ($entry = $targetDirectory->read())) {
            if ($this->matchDirectory($entry) === false) {
                continue;
            }

            $absoluteFilePath = $currentDirectory . '/' . $entry;

            if (is_file($absoluteFilePath)) {
                yield $absoluteFilePath;
            } else if (is_dir($absoluteFilePath)) {
                $files = $this->findFiles($absoluteFilePath);

                foreach ($files as $file) {
                    yield $file;
                }
            }
        }

        $targetDirectory->close();
    }

}
