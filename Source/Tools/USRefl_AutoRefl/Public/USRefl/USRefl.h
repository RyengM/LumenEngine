#pragma once

#include "config.h"

#include "Attr.h"
#include "AttrList.h"
#include "Base.h"
#include "BaseList.h"
#include "ElemList.h"
#include "Field.h"
#include "FieldList.h"
#include "NamedValue.h"
#include "TypeInfo.h"
#include "TypeInfoBase.h"
#include "Util.h"

// To access private member and mark the reflective object
// There is no ';' for antlr parse
#define REFLECTION_REGISTRATION(Typename) friend Ubpa::USRefl::TypeInfo<Typename>