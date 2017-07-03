/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/


#pragma once

namespace cubevoid {
	namespace math {

		template <class T, int n>
		class Vec
		{
		public:

		private:
			T data_[n];
		};

		template <class T>
		using Vec2 = Vec<T, 2>;

		template <class T>
		using Vec3 = Vec<T, 3>;

		template <class T>
		using Vec4 = Vec<T, 4>;

	}
}