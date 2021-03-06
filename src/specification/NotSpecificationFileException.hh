<?hh //strict

/**
 * This file is part of hhspecify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhspecify\specification;

use \Exception;

class NotSpecificationFileException extends Exception
{

    public function __construct(
        protected string $message = '',
        protected int $code = 0,
        protected ?Exception $previous = null
    )
    {
        parent::__construct($message, $code, $previous);
    }

}
