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

#include "laipinyin_engine_proxy.h"
#include "laipinyin_engine.h"

#define IBUS_laipinyin_ENGINE(obj) \
    (G_TYPE_CHECK_INSTANCE_CAST ((obj), IBUS_TYPE_laipinyin_ENGINE, IBuslaipinyinEngine))

#define IBUS_IS_laipinyin_ENGINE(obj) \
    (G_TYPE_CHECK_INSTANCE_TYPE ((obj), IBUS_TYPE_laipinyin_ENGINE))

#define IBUS_laipinyin_ENGINE_GET_CLASS(obj) \
    (G_TYPE_INSTANCE_GET_CLASS ((obj), IBUS_TYPE_laipinyin_ENGINE, IBuslaipinyinEngineClass))

extern IBusEngineClass *parent_class;

struct IBuslaipinyinEngine {
    IBusEngine parent;

    /* members */
    laipinyinEngine *engine;
};

#define GET_PY_ENGINE(__engine__)               \
    (((IBuslaipinyinEngine *)(__engine__))->engine)


void
ibus_laipinyin_engine_init(IBusEngine *py_engine)
{
    if (g_object_is_floating (py_engine))
        g_object_ref_sink (py_engine);
    GET_PY_ENGINE(py_engine) = new laipinyinEngine(IBUS_ENGINE(py_engine));
}

void
ibus_laipinyin_engine_destroy(IBusEngine *py_engine)
{
    
    delete GET_PY_ENGINE(py_engine);
    GET_PY_ENGINE(py_engine) = NULL;
    IBUS_OBJECT_CLASS (parent_class)->destroy( IBUS_OBJECT(py_engine));
}

gboolean
ibus_laipinyin_engine_process_key_event(IBusEngine *engine,
                                        guint keyval,
                                        guint keycode,
                                        guint modifiers)
{
    if (GET_PY_ENGINE(engine)->is_valid()) {
        return GET_PY_ENGINE(engine)->process_key_event(keyval, keycode, modifiers) ?
            TRUE : FALSE;
    } else {
        return FALSE;
    }
}

void
ibus_laipinyin_engine_property_activate (IBusEngine *engine,
                                         const gchar *prop_name,
                                         guint prop_state)
{
    if (GET_PY_ENGINE(engine)->is_valid()) {
        GET_PY_ENGINE(engine)->property_activate(prop_name, prop_state);
    }
}

void ibus_laipinyin_engine_candidate_clicked (IBusEngine *engine,
                                              guint index,
                                              guint button,
                                              guint state)
{
    GET_PY_ENGINE(engine)->candidate_clicked(index);
}

#define IMPL_WITH(name)                                   \
    void                                                  \
    ibus_laipinyin_engine_##name (IBusEngine *engine)     \
    {                                                     \
        IBuslaipinyinEngine *py_engine =                  \
            (IBuslaipinyinEngine *) engine;               \
        if (py_engine->engine->is_valid()) {              \
            py_engine->engine->name();                    \
        }                                                 \
        parent_class->name (engine);                      \
    }

IMPL_WITH(focus_in)
IMPL_WITH(focus_out)
IMPL_WITH(reset)
IMPL_WITH(enable)
IMPL_WITH(disable)
IMPL_WITH(page_up)
IMPL_WITH(page_down)
IMPL_WITH(cursor_up)
IMPL_WITH(cursor_down)

// -*- indent-tabs-mode: nil -*- vim:et:ts=4
