#pragma once

#include <core/vec.hpp>
#include <core/mesh.hpp>

template <class Iterator, class IntoT, int Version = 0>
bool Parse(Iterator from, Iterator to, IntoT& into);

//template <class Iterator>
//bool Parse(Iterator from, Iterator to, Mesh& mesh)
//{
//	return qi::parse(from, to, double_);
//}