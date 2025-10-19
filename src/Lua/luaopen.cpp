/*                        L U A O P E N . C P P
 * BRL-CAD
 *
 * Copyright (c) 2020-2025 United States Government as represented by
 * the U.S. Army Research Laboratory.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/** @file arb8.h
 *
 *  BRL-CAD Lua scripting:
 *      Lua module load hook
 */

#include "lua.hpp"

#include "arb8.h"
#include "database.h"
#include "ellipsoid.h"
#include "ellipticaltorus.h"
#include "halfspace.h"
#include "hyperboliccylinder.h"
#include "hyperboloid.h"
#include "paraboliccylinder.h"
#include "paraboloid.h"
#include "particle.h"
#include "sphere.h"
#include "torus.h"
#include "vector3d.h"


static const luaL_Reg BrlcadEntryPoints[] = {
    {"Arb8",               CreateArb8},
    {"Database",           CreateDatabase},
    {"Ellipsoid",          CreateEllipsoid},
    {"EllipticalTorus",    CreateEllipticalTorus},
    {"Halfspace",          CreateHalfspace},
    {"HyperbolicCylinder", CreateHyperbolicCylinder},
    {"Hyperboloid",        CreateHyperboloid},
    {"ParabolicCylinder",  CreateParabolicCylinder},
    {"Paraboloid",         CreateParaboloid},
    {"Particle",           CreateParticle},
    {"Sphere",             CreateSphere},
    {"Torus",              CreateTorus},
    {"Vector3D",           CreateVector3D},
    {nullptr, nullptr}
};


extern "C" int BRLCAD_MOOSE_EXPORT luaopen_brlcad
(
    lua_State* luaState
) {
    luaL_newlib(luaState, BrlcadEntryPoints);

    return 1;
}
