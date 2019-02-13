#pragma once

#include "3ds/types.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <assert.h>

#define BIT(x) (1 << (x))

#define GPU_TEVSOURCES(a, b, c) (0)
#define GPU_TEVOPERANDS(a, b, c) (0)

#define FIXME_HACK() { assert(false); }

#define SHADER(name) \
  const void* name = NULL; \
  const int name ## _size = 0;

typedef struct {
  int a;
  int b;
  u8* c;
} FS_path;

typedef struct {
  u32 a;
  FS_path b;
} FS_archive;

#define FS_OPEN_READ BIT(0)
#define FS_OPEN_WRITE BIT(1)
#define FS_OPEN_CREATE BIT(2)

#define FS_WRITE_FLUSH 0

#define FS_ATTRIBUTE_NONE 0

#define PATH_CHAR 1
#define PATH_EMPTY 0

typedef void* Handle;
typedef int Result;

typedef struct {
  int px;
  int py;
} touchPosition;

typedef struct {
  int dx;
  int dy;
} circlePosition;

enum {
  GSPEVENT_VBlank0,
};

enum {
  GPU_CULL_BACK_CCW,
  GPU_REPLACE,
  GPU_ALWAYS,
  GPU_KEEP,
  GPU_GREATER,
  GPU_WRITE_ALL,
  GPU_FLOAT,
  GPU_RGBA8,
  GPU_NEAREST,
  GPU_BLEND_ADD,
  GPU_SRC_ALPHA,
  GPU_ONE_MINUS_SRC_ALPHA,
  GPU_TEXUNIT0,
  GPU_REPEAT,
  GPU_MODULATE,
};

#define GPU_TEXTURE_WRAP_S(x) (x)
#define GPU_TEXTURE_WRAP_T(x) (x)
#define GPU_ATTRIBFMT(a, b, c) (0)
#define GPU_TEXTURE_MAG_FILTER(x) (x)
#define GPU_TEXTURE_MIN_FILTER(x) (x)

typedef enum {
  GPU_TRIANGLES,
} GPU_Primitive_t;

typedef enum {
  GFX_TOP,
  GFX_BOTTOM,
} gfxScreen_t;

typedef enum {
  GFX_RIGHT,
  GFX_LEFT
} gfx3dSide_t;

#define KEY_A BIT(0)
#define KEY_B BIT(1)
#define KEY_X BIT(2)
#define KEY_Y BIT(3)
#define KEY_START BIT(4)
#define KEY_SELECT BIT(5)
#define KEY_DRIGHT BIT(6)
#define KEY_DLEFT BIT(7)
#define KEY_DDOWN BIT(8)
#define KEY_DUP BIT(9)
#define KEY_L BIT(10)
#define KEY_R BIT(11)
#define KEY_ZL BIT(12)
#define KEY_ZR BIT(13)
#define KEY_TOUCH BIT(14)

static void srvInit() FIXME_HACK()
static void aptInit() FIXME_HACK()
static void gfxInit() FIXME_HACK()
static void fsInit() FIXME_HACK()
static void hidInit(bool x) FIXME_HACK()
static void irrstInit(bool x) FIXME_HACK()
static void gfxSet3D(bool x) FIXME_HACK()

static void irrstExit() FIXME_HACK()
static void hidExit() FIXME_HACK()
static void fsExit() FIXME_HACK()
static void gfxExit() FIXME_HACK()
static void aptExit() FIXME_HACK()
static void srvExit() FIXME_HACK()

// A macro because some params won't exist + needs full redesign?
typedef struct {
  int pad;
} DVLB_s;
#define SHDR_ParseSHBIN(a, b) (assert(false), 0)
#define SHDR_GetUniformRegister(a, b, c) (assert(false), 0)

static void gspWaitForEvent(int a, int b) FIXME_HACK()
static void gspWaitForP3D() FIXME_HACK()
static void gspWaitForPPF() FIXME_HACK()
static void gspWaitForPSC0() FIXME_HACK()

static void GX_SetDisplayTransfer(void* a, u32* b, u32 c, u32* d, u32 e, u32 f) FIXME_HACK()

static void GPU_DepthRange(float a, float b) FIXME_HACK()
static void GPU_SetFaceCulling(int a) FIXME_HACK()
static void GPU_SetStencilTest(bool a, int b, uint8_t c, uint8_t d, uint8_t e) FIXME_HACK()
static void GPU_SetViewport(u32* a, u32* b, int c, int d, int e, int f) FIXME_HACK()
static void GPU_SetStencilOp(int a, int b, int c) FIXME_HACK()
static void GPU_SetBlendingColor(int a, int b, int c, int d) FIXME_HACK()

static void GPUCMD_Finalize() FIXME_HACK()
static void GPUCMD_GetBuffer(void* a, void* b, u32* c) FIXME_HACK()
static void GPUCMD_FlushAndRun(void* a) FIXME_HACK()



// Hacks:

static void aptCloseSession() FIXME_HACK()
static void aptOpenSession() FIXME_HACK()

static Result APT_SetAppCpuTimeLimit(void* a, int b) FIXME_HACK()

static void FSFILE_Close(int a, ...) FIXME_HACK()
static Result FSFILE_GetSize(int a, ...) FIXME_HACK()
static Result FSFILE_Read(int a, ...) FIXME_HACK()
static Result FSFILE_Write(int a, ...) FIXME_HACK()

static int FS_makePath(int a, ...) FIXME_HACK()

static Result FSUSER_OpenArchive(void* a, ...) FIXME_HACK()
static Result FSUSER_OpenFile(int a, ...) FIXME_HACK()

static void* gfxGetFramebuffer(int a, ...) FIXME_HACK()

static void GPUCMD_AddSingleParam(int a, ...) FIXME_HACK()

static u32* gpuCmdBuf = NULL;
static u32 gpuCmdBufOffset = 0;

static void GPUCMD_SetBuffer(int a, ...) FIXME_HACK()
static void GPUCMD_SetBufferOffset(int a, ...) FIXME_HACK()

static void GPU_Init(int a, ...) FIXME_HACK()
static void GPU_SetAlphaBlending(int a, ...) FIXME_HACK()
static void GPU_SetAlphaTest(int a, ...) FIXME_HACK()
static void GPU_SetAttributeBuffers(int a, ...) FIXME_HACK()
static void GPU_SetDepthTestAndWriteMask(int a, ...) FIXME_HACK()
static void GPU_SetTexEnv(int a, ...) FIXME_HACK()
static void GPU_SetTextureEnable(int a, ...) FIXME_HACK()
static void GPU_SetTexture(int a, ...) FIXME_HACK()
static void GPU_SetUniform(int a, ...) FIXME_HACK()

static void GSPGPU_FlushDataCache(int a, ...) FIXME_HACK()

static void hidCircleRead(int a, ...) FIXME_HACK()
static void hidCstickRead(int a, ...) FIXME_HACK()
static int hidKeysDown() FIXME_HACK()
static int hidKeysHeld() FIXME_HACK()
static void hidTouchRead(int a, ...) FIXME_HACK()

static int keysDown() FIXME_HACK()
static int keysHeld() FIXME_HACK()

static void* linearAlloc(size_t a) FIXME_HACK()
static void linearFree(void* a) FIXME_HACK()
static void* linearMemAlign(void* a, size_t b) FIXME_HACK()
static int linearSpaceFree() FIXME_HACK()

static u32 osConvertVirtToPhys(u32 a) FIXME_HACK()

static void SHDR_UseProgram(int a, ...) FIXME_HACK()

static void svcCloseHandle(int a, ...) FIXME_HACK()
static void svcCreateMutex(int a, ...) FIXME_HACK()
static Result svcCreateThread(int a, ...) FIXME_HACK()
static void svcExitThread() FIXME_HACK()
static void svcReleaseMutex(int a, ...) FIXME_HACK()
static void svcSleepThread(int a, ...) FIXME_HACK()
static void svcWaitSynchronization(int a, ...) FIXME_HACK()


// gs assembly:
static void _vboMemcpy50(u32* dst, u32* src) FIXME_HACK()

// Unknown
static u8 __end__[1];
static u8* fake_heap_end = NULL;

