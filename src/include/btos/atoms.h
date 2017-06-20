#ifndef _ATOMS_H
#define _ATOMS_H
#include <util/bt_enum.h>

ENUM_START(bt_atom_modify)
	ENUM_SET(bt_atom_modify, Set, 0),
	ENUM_SET(bt_atom_modify, Add, 1),
	ENUM_SET(bt_atom_modify, Subtract, 2),
	ENUM_SET(bt_atom_modify, Or, 3),
	ENUM_SET(bt_atom_modify, And, 4),
ENUM_END
ENUM_TYPE(bt_atom_modify);

ENUM_START(bt_atom_compare)
	ENUM_SET(bt_atom_compare, Equal, 1),
	ENUM_SET(bt_atom_compare, NotEqual, 2),
	ENUM_SET(bt_atom_compare, LessThan, 3),
	ENUM_SET(bt_atom_compare, GreaterThan, 4),
ENUM_END
ENUM_TYPE(bt_atom_compare);

#endif
