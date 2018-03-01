/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016, 2017, 2018
              Vladimír Vondruš <mosra@centrum.cz>
    Copyright © 2015 Jonathan Hale <squareys@googlemail.com>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <sstream>
#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Buffer.h"

namespace Magnum { namespace Test {

struct BufferTest: TestSuite::Tester {
    explicit BufferTest();

    void constructNoCreate();

    void debugTargetHint();
    #ifndef MAGNUM_TARGET_GLES2
    void debugTarget();
    #endif
};

BufferTest::BufferTest() {
    addTests({&BufferTest::constructNoCreate,

              &BufferTest::debugTargetHint,
              #ifndef MAGNUM_TARGET_GLES2
              &BufferTest::debugTarget
              #endif
              });
}

void BufferTest::constructNoCreate() {
    {
        Buffer buffer{NoCreate};
        CORRADE_COMPARE(buffer.id(), 0);
    }

    CORRADE_VERIFY(true);
}

void BufferTest::debugTargetHint() {
    std::ostringstream out;
    Debug{&out} << Buffer::TargetHint::Array << Buffer::TargetHint(0xdead);
    CORRADE_COMPARE(out.str(), "Buffer::TargetHint::Array Buffer::TargetHint(0xdead)\n");
}

#ifndef MAGNUM_TARGET_GLES2
void BufferTest::debugTarget() {
    std::ostringstream out;
    Debug{&out} << Buffer::Target::Uniform << Buffer::Target(0xdead);
    CORRADE_COMPARE(out.str(), "Buffer::Target::Uniform Buffer::Target(0xdead)\n");
}
#endif

}}

CORRADE_TEST_MAIN(Magnum::Test::BufferTest)
