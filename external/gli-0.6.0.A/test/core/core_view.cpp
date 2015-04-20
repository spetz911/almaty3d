///////////////////////////////////////////////////////////////////////////////////
/// OpenGL Image (gli.g-truc.net)
///
/// Copyright (c) 2008 - 2013 G-Truc Creation (www.g-truc.net)
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this software and associated documentation files (the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
/// 
/// The above copyright notice and this permission notice shall be included in
/// all copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
/// THE SOFTWARE.
///
/// @ref core
/// @file gli/core/core_view.cpp
/// @date 2013-02-03 / 2013-02-03
/// @author Christophe Riccio
///////////////////////////////////////////////////////////////////////////////////

#include <gli/gli.hpp>
#include <gli/core/levels.hpp>

int test_view1D
(
	std::vector<gli::format> const & Formats,
	gli::texture1D::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::texture1D TextureA(Formats[i], TextureSize);
		gli::texture1D TextureViewA(TextureA, TextureA.base_level(), TextureA.max_level());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::texture1D TextureViewC = gli::view(TextureA, TextureA.base_level(), TextureA.max_level());

		Error += TextureA == TextureViewC ? 0 : 1;
		Error += TextureViewA == TextureViewC ? 0 : 1;

		gli::texture1D TextureB(Formats[i], TextureSize / gli::texture1D::dim_type(2));
		gli::texture1D TextureViewB(TextureA, TextureA.base_level() + 1, TextureA.max_level());

		Error += TextureB == TextureViewB ? 0 : 1;

		gli::texture1D TextureViewD = gli::view(TextureA, TextureA.base_level() + 1, TextureA.max_level());

		Error += TextureB == TextureViewD ? 0 : 1;
		Error += TextureViewB == TextureViewD ? 0 : 1;

		gli::texture1D TextureD(TextureA, 1, 3);

		Error += TextureA[1] == TextureD[0] ? 0 : 1;
		Error += TextureA[2] == TextureD[1] ? 0 : 1;

		gli::texture1D TextureE(TextureD, 1, 1);

		Error += TextureE[0] == TextureD[1] ? 0 : 1;
		Error += TextureE[0] == TextureA[2] ? 0 : 1;
	}

	return Error;
}

int test_view1DArray
(
	std::vector<gli::format> const & Formats,
	gli::texture1DArray::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::texture1DArray TextureA(gli::texture1DArray::size_type(4), Formats[i], TextureSize);

		gli::texture1DArray TextureViewA(TextureA, 
			TextureA.baseLayer(), TextureA.maxLayer(), 
			TextureA.baseLevel(), TextureA.maxLevel());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::texture1DArray TextureViewC = gli::view(TextureA, 
			TextureA.baseLayer(), TextureA.maxLayer(), 
			TextureA.baseLevel(), TextureA.maxLevel());
		
		Error += TextureA == TextureViewC ? 0 : 1;
		Error += TextureViewC == TextureViewA ? 0 : 1;

		gli::texture1DArray TextureB(gli::texture1DArray::size_type(4), Formats[i], TextureSize / gli::texture1DArray::dim_type(2));

		Error += TextureA != TextureB ? 0 : 1;

		gli::texture1DArray TextureViewB(TextureA,
			TextureA.baseLayer(), TextureA.maxLayer(),
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureA != TextureViewB ? 0 : 1;
		Error += TextureB == TextureViewB ? 0 : 1;

		gli::texture1DArray TextureViewD = gli::view(TextureA, 
			TextureA.baseLayer(), TextureA.maxLayer(), 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureViewD == TextureViewB ? 0 : 1;

		gli::texture1DArray TextureD(TextureA, 0, TextureA.layers() -1, 1, 3);

		Error += TextureA[0][1] == TextureD[0][0] ? 0 : 1;
		Error += TextureA[0][2] == TextureD[0][1] ? 0 : 1;

		gli::texture1DArray TextureE(TextureD, 0, TextureD.layers() -1, 0, TextureD.levels() - 1);

		Error += TextureE == TextureD ? 0 : 1;
		Error += TextureE[0] == TextureD[0] ? 0 : 1;

		gli::texture1DArray TextureF(TextureE, 1, 3, 0, TextureE.levels() - 1);

		Error += TextureF[0] == TextureD[1] ? 0 : 1;
		Error += TextureF[0] == TextureE[1] ? 0 : 1;
	}

	return Error;
}

int test_view2D
(
	std::vector<gli::format> const & Formats,
	gli::texture2D::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::texture2D TextureA(gli::levels(TextureSize), Formats[i], TextureSize);

		for(std::size_t Index = 0; Index < TextureA.size<glm::byte>(); ++Index)
			*(TextureA.data<glm::byte>() + Index) = glm::byte(Index);

		gli::texture2D TextureViewA(TextureA, TextureA.baseLevel(), TextureA.maxLevel());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::texture2D TextureD(TextureA, 1, 3);

		Error += TextureA[1] == TextureD[0] ? 0 : 1;
		Error += TextureA[2] == TextureD[1] ? 0 : 1;

		gli::texture2D TextureE(TextureD, 1, 1);

		Error += TextureE[0] == TextureD[1] ? 0 : 1;
		Error += TextureE[0] == TextureA[2] ? 0 : 1;

		gli::texture2D TextureViewB(TextureA, 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		gli::texture2D TextureViewD = gli::view(TextureA, 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureViewD == TextureViewB ? 0 : 1;
	}

	return Error;
}

int test_view2DArray
(
	std::vector<gli::format> const & Formats, 
	gli::texture2DArray::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::texture2DArray TextureA(gli::texture2DArray::size_type(4), gli::levels(TextureSize), Formats[i], TextureSize);

		gli::texture2DArray TextureViewA(TextureA, 
			TextureA.baseLayer(), TextureA.maxLayer(), 
			TextureA.baseLevel(), TextureA.maxLevel());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::texture2DArray TextureB(gli::texture2DArray::size_type(4), Formats[i], TextureSize / gli::texture2DArray::dim_type(2));

		gli::texture2DArray TextureViewB(TextureA, 
			TextureA.baseLayer(), TextureA.maxLayer(), 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		gli::texture2DArray TextureViewD = gli::view(TextureA, 
			TextureA.baseLayer(), TextureA.maxLayer(), 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureViewB == TextureViewD ? 0 : 1;
		Error += TextureB == TextureViewB ? 0 : 1;

		gli::texture2DArray TextureD(TextureA, 0, TextureA.layers() -1, 1, 3);

		Error += TextureA[0][1] == TextureD[0][0] ? 0 : 1;
		Error += TextureA[0][2] == TextureD[0][1] ? 0 : 1;

		gli::texture2DArray TextureE(TextureD, 0, TextureD.layers() -1, 0, TextureD.levels() - 1);

		Error += TextureE == TextureD ? 0 : 1;
		Error += TextureE[0] == TextureD[0] ? 0 : 1;

		gli::texture2DArray TextureF(TextureE, 1, 3, 0, TextureE.levels() - 1);

		Error += TextureF[0] == TextureD[1] ? 0 : 1;
		Error += TextureF[0] == TextureE[1] ? 0 : 1;
	}

	return Error;
}

int test_view3D
(
	std::vector<gli::format> const & Formats, 
	gli::texture3D::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::texture3D TextureA(gli::levels(TextureSize), Formats[i], TextureSize);
		gli::texture3D TextureViewA(TextureA, TextureA.baseLevel(), TextureA.maxLevel());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::texture3D::dim_type SizeB(TextureSize / gli::texture3D::dim_type(2));
		gli::texture3D TextureB(gli::levels(SizeB), Formats[i], SizeB);

		gli::texture3D TextureViewB(TextureA, 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureB == TextureViewB ? 0 : 1;

		gli::texture3D TextureViewD = gli::view(TextureA, 
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureViewD == TextureViewB ? 0 : 1;

		gli::texture3D TextureD(TextureA, 1, 3);

		Error += TextureA[1] == TextureD[0] ? 0 : 1;
		Error += TextureA[2] == TextureD[1] ? 0 : 1;

		gli::texture3D TextureE(TextureD, 1, 1);

		Error += TextureE[0] == TextureD[1] ? 0 : 1;
		Error += TextureE[0] == TextureA[2] ? 0 : 1;
	}

	return Error;
}

int test_viewCube
(
	std::vector<gli::format> const & Formats, 
	gli::textureCube::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::textureCube TextureA(gli::textureCube::size_type(6), gli::levels(TextureSize), Formats[i], TextureSize);

		gli::textureCube TextureViewA(TextureA,
			TextureA.baseFace(), TextureA.maxFace(),
			TextureA.baseLevel(), TextureA.maxLevel());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::textureCube::dim_type SizeB(TextureSize / gli::textureCube::dim_type(2));
		gli::textureCube TextureB(gli::textureCube::size_type(6), gli::levels(SizeB), Formats[i], SizeB);

		gli::textureCube TextureViewB(TextureA, TextureA.baseFace(), TextureA.maxFace(), TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureB == TextureViewB ? 0 : 1;

		gli::textureCube TextureViewD = gli::view(TextureA, TextureA.baseFace(), TextureA.maxFace(), TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureViewD == TextureViewB ? 0 : 1;

		gli::textureCube TextureD(TextureA, 0, TextureA.faces() -1, 1, 3);

		Error += TextureA[0][1] == TextureD[0][0] ? 0 : 1;
		Error += TextureA[0][2] == TextureD[0][1] ? 0 : 1;

		gli::textureCube TextureE(TextureD, 0, TextureD.faces() -1, 0, TextureD.levels() - 1);

		Error += TextureE == TextureD ? 0 : 1;
		Error += TextureE[0] == TextureD[0] ? 0 : 1;

		gli::textureCube TextureF(TextureE, 1, 3, 0, TextureE.levels() - 1);

		Error += TextureF[0] == TextureD[1] ? 0 : 1;
		Error += TextureF[0] == TextureE[1] ? 0 : 1;
	}

	return Error;
}

int test_viewCubeArray
(
	std::vector<gli::format> const & Formats,
	gli::textureCubeArray::dim_type const & TextureSize
)
{
	int Error(0);

	for(std::size_t i = 0; i < Formats.size(); ++i)
	{
		gli::textureCubeArray TextureA(
			gli::textureCubeArray::size_type(4),
			gli::textureCubeArray::size_type(6),
			gli::levels(TextureSize),
			Formats[i],
			TextureSize);

		gli::textureCubeArray TextureViewA(TextureA,
			TextureA.baseLayer(), TextureA.maxLayer(),
			TextureA.baseFace(), TextureA.maxFace(),
			TextureA.baseLevel(), TextureA.maxLevel());

		Error += TextureA == TextureViewA ? 0 : 1;

		gli::textureCubeArray::dim_type SizeB(TextureSize / gli::textureCubeArray::dim_type(2));
		gli::textureCubeArray TextureB(
			gli::textureCubeArray::size_type(4),
			gli::textureCubeArray::size_type(6),
			gli::levels(SizeB),
			Formats[i],
			SizeB);

		gli::textureCubeArray TextureViewB(TextureA,
			TextureA.baseLayer(), TextureA.maxLayer(),
			TextureA.baseFace(), TextureA.maxFace(),
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureB == TextureViewB ? 0 : 1;

		gli::textureCubeArray TextureViewD(TextureA,
			TextureA.baseLayer(), TextureA.maxLayer(),
			TextureA.baseFace(), TextureA.maxFace(),
			TextureA.baseLevel() + 1, TextureA.maxLevel());

		Error += TextureViewD == TextureViewB ? 0 : 1;

		gli::textureCubeArray TextureD(TextureA, 0, TextureA.layers() -1, 0, TextureA.faces() -1, 1, 3);

		Error += TextureA[0][0][1] == TextureD[0][0][0] ? 0 : 1;
		Error += TextureA[0][0][2] == TextureD[0][0][1] ? 0 : 1;

		gli::textureCubeArray TextureE(TextureD, 0, TextureA.layers() -1, 0, TextureD.faces() -1, 0, TextureD.levels() - 1);

		Error += TextureE == TextureD ? 0 : 1;
		Error += TextureE[0] == TextureD[0] ? 0 : 1;
		Error += TextureE[1] == TextureD[1] ? 0 : 1;

		gli::textureCubeArray TextureF(TextureE, 0, TextureA.layers() -1, 1, 3, 0, TextureE.levels() - 1);

		Error += TextureF[0][0] == TextureD[0][1] ? 0 : 1;
		Error += TextureF[1][0] == TextureD[1][1] ? 0 : 1;
		Error += TextureF[0][0] == TextureE[0][1] ? 0 : 1;
		Error += TextureF[1][0] == TextureE[1][1] ? 0 : 1;
	}

	return Error;
}

int main()
{
	int Error(0);

	std::vector<gli::format> Formats;
	Formats.push_back(gli::RGBA8_UNORM);
	Formats.push_back(gli::RGB8_UNORM);
	Formats.push_back(gli::R8_SNORM);
	Formats.push_back(gli::RGB_DXT1);
	Formats.push_back(gli::RGB_BP_UNORM);
	Formats.push_back(gli::RGBA32F);
	std::size_t const TextureSize(32);

	Error += test_view1D(Formats, gli::texture1D::dim_type(TextureSize));
	Error += test_view1DArray(Formats, gli::texture1DArray::dim_type(TextureSize));
	Error += test_view2D(Formats, gli::texture2D::dim_type(TextureSize));
	Error += test_view2DArray(Formats, gli::texture2DArray::dim_type(TextureSize));
	Error += test_view3D(Formats, gli::texture3D::dim_type(TextureSize));
	Error += test_viewCube(Formats, gli::textureCube::dim_type(TextureSize));
	Error += test_viewCubeArray(Formats, gli::textureCube::dim_type(TextureSize));

	return Error;
}
