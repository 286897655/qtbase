/****************************************************************************
**
** Copyright (C) 2015 Intel Corporation.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <atomic>
#include <cstdint>

void test(volatile std::atomic<std::int64_t> &a)
{
    std::int64_t v = a.load(std::memory_order_acquire);
    while (!a.compare_exchange_strong(v, v + 1,
                                      std::memory_order_acq_rel,
                                      std::memory_order_acquire)) {
        v = a.exchange(v - 1);
    }

    a.store(v + 1, std::memory_order_release);
}

int main(int, char **)
{
    void *ptr = (void*)0xffffffc0; // any random pointer
    test(*reinterpret_cast<std::atomic<std::int64_t> *>(ptr));
    return 0;
}
