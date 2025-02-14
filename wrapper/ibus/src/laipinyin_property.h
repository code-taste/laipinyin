/*
 * Copyright (c) 2009 Kov Chai <tchaikov@gmail.com>
 *
 * The contents of this file are subject to the terms of either the GNU Lesser
 * General Public License Version 2.1 only ("LGPL") or the Common Development and
 * Distribution License ("CDDL")(collectively, the "License"). You may not use this
 * file except in compliance with the License. You can obtain a copy of the CDDL at
 * http://www.opensource.org/licenses/cddl1.php and a copy of the LGPLv2.1 at
 * http://www.opensource.org/licenses/lgpl-license.php. See the License for the
 * specific language governing permissions and limitations under the License. When
 * distributing the software, include this License Header Notice in each file and
 * include the full text of the License in the License file as well as the
 * following notice:
 *
 * NOTICE PURSUANT TO SECTION 9 OF THE COMMON DEVELOPMENT AND DISTRIBUTION LICENSE
 * (CDDL)
 * For Covered Software in this distribution, this License shall be governed by the
 * laws of the State of California (excluding conflict-of-law provisions).
 * Any litigation relating to this License shall be subject to the jurisdiction of
 * the Federal Courts of the Northern District of California and the state courts
 * of the State of California, with venue lying in Santa Clara County, California.
 *
 * Contributor(s):
 *
 * If you wish your version of this file to be governed by only the CDDL or only
 * the LGPL Version 2.1, indicate your decision by adding "[Contributor]" elects to
 * include this software in this distribution under the [CDDL or LGPL Version 2.1]
 * license." If you don't indicate a single choice of license, a recipient has the
 * option to distribute your version of this file under either the CDDL or the LGPL
 * Version 2.1, or to extend the choice of license to its licensees as provided
 * above. However, if you add LGPL Version 2.1 code and therefore, elected the LGPL
 * Version 2 license, then the option applies only if the new code is made subject
 * to such option by the copyright holder.
 */

#ifndef laipinyin_PROPERTY_H
#define laipinyin_PROPERTY_H

#include <string>
#include "ibus_common.h"

struct PropertyInfo
{
    PropertyInfo();
    ~PropertyInfo();

    std::string icon;
    ibus::Text  label;
    ibus::Text  tooltip;
};

class laipinyinProperty : public ibus::Property
{
    ibus::Engine      m_engine;
    const std::string m_name;
    PropertyInfo      m_info[2];
    bool              m_state;

public:
    static laipinyinProperty create_status_prop(ibus::Engine engine,
                                                bool state = true);
    static laipinyinProperty create_letter_prop(ibus::Engine engine,
                                                bool state = false);
    static laipinyinProperty create_punct_prop(ibus::Engine engine,
                                                bool state = false);
    virtual ~laipinyinProperty();
    bool toggle(const std::string& name);
    void update(bool state);
    bool state() const;

private:
    void init(bool state);
    laipinyinProperty(ibus::Engine engine, const std::string& name);
};

class SetupLauncher : public ibus::Property
{
    const std::string m_name;
    PropertyInfo      m_info;

public:
    SetupLauncher();
    void launch(const std::string& name);
    void init();
};


#endif // laipinyin_PROPERTY_H

// -*- indent-tabs-mode: nil -*- vim:et:ts=4
