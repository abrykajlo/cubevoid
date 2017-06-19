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