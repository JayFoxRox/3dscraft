#pragma once

#include "3ds/types.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <stdio.h>
#include <assert.h>

#include <threads.h>

#include <SDL2/SDL.h>

extern SDL_GameController* controller;


// Helper to work with 3DS handles:

typedef int Handle;




#define BIT(x) (1 << (x))

#define GPU_TEVSOURCES(a, b, c) (0)
#define GPU_TEVOPERANDS(a, b, c) (0)

#define RAW_FILE(name, path) \
  void* name = NULL; \
  size_t name ## _size = 0; \
  static __attribute__((constructor)) void name ## _loader() { \
    printf("Loading '%s'\n", path); \
    FILE* f = fopen(path, "rb"); \
    assert(f != NULL); \
    fseek(f, 0, SEEK_END); \
    name ## _size = ftell(f); \
    fseek(f, 0, SEEK_SET); \
    name = malloc(name ## _size); \
    fread(name, 1, name ## _size, f); \
    fclose(f); \
  }

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

typedef int Result;

typedef struct {
  u16 px;
  u16 py;
} touchPosition;

typedef struct {
  s16 dx;
  s16 dy;
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
//#define KEY_X BIT(2)
//#define KEY_Y BIT(3)
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

// A macro because some params won't exist + needs full redesign?
typedef struct {
  int pad;
} DVLB_s;

static u32* gpuCmdBuf = NULL;
static u32 gpuCmdBufOffset = 0;

static u32* gxCmdBuf = NULL;

// gs assembly:
//static void _vboMemcpy50(u32* dst, u32* src) FIXME_HACK()

// Unknown
static u8 __end__[1];
static u8* fake_heap_end = NULL;


void srvInit();
void aptInit();
void gfxInit();
void fsInit();
void hidInit(bool x);
void irrstInit(bool x);
void gfxSet3D(bool x);
void* SHDR_ParseSHBIN(u32* a, size_t b);
u32 SHDR_GetUniformRegister(void* a, char* b, int c);
void SHDR_UseProgram(void* a, int b);
void gspWaitForEvent(int a, int b);
void gspWaitForP3D();
void gspWaitForPPF();
void gspWaitForPSC0();
void GX_SetMemoryFill(u32* a, ...);
void GX_SetDisplayTransfer(void* a, u32* b, u32 c, u32* d, u32 e, u32 f);
void GPU_DepthRange(float a, float b);
void GPU_SetFaceCulling(int a);
void GPU_SetStencilTest(bool a, int b, uint8_t c, uint8_t d, uint8_t e);
void GPU_SetViewport(u32* a, u32* b, int c, int d, int e, int f);
void GPU_SetStencilOp(int a, int b, int c);
void GPU_SetBlendingColor(int a, int b, int c, int d);
void GPU_FinishDrawing();
void GPUCMD_Finalize();
void GPUCMD_GetBuffer(void* a, void* b, u32* c);
void GPUCMD_FlushAndRun(void* a);
void aptCloseSession();
void aptOpenSession();
bool aptMainLoop();
Result APT_SetAppCpuTimeLimit(void* a, int b);
Result FSFILE_GetSize(Handle a, u64* b);
Result FSFILE_Read(Handle a, u32* b, u32 c, void* d, u32 e);
Result FSFILE_Write(Handle a, u32* b, u32 c, const void* d, u32 e, u32 f);
char* FS_makePath(int a, char* b);
Result FSUSER_OpenArchive(void* a, void* b);
Result FSUSER_OpenFile(void* a, Handle* b, FS_archive c, char* d, int e, int f);
void* gfxGetFramebuffer(int a, int b, u16* c, u16* d);
void gfxSwapBuffersGpu();
void GPUCMD_SetBufferOffset(int a);
void GPU_Reset(u32* a, ...);
void GPU_Init(void* a);
void GPU_SetAlphaBlending(int a, int b, int c, int d, int e, int f);
void GPU_SetAlphaTest(bool a, int b, uint8_t c);
void GPU_SetAttributeBuffers(int a, ...);
void GPU_SetDepthTestAndWriteMask(int a, int b, int c);
void GPU_SetTexEnv(int a, int b, int c, int d, int e, int f, int g, u32 h);
void GPU_SetTextureEnable(int a);
void GPU_SetTexture(int a, u32* b, int width, int height, int filter, int format);
void GPU_SetUniform(u32 reg, u32* values, int count); //FIXME: Implement
void GPU_DrawArrayDirectly(GPU_Primitive_t primitive, u8* data, u32 n);
void GSPGPU_FlushDataCache(void* a, u8* b, size_t c);
void hidScanInput();
void hidCircleRead(circlePosition* a);
void hidCstickRead(circlePosition* a);
int hidKeysHeld();
int hidKeysDown();
void hidTouchRead(touchPosition* a);
int keysDown();
int keysHeld();
void* linearAlloc(u32 a);
void linearFree(void* a);
void* linearMemAlign(u32 a, u32 b);
u32 osConvertVirtToPhys(u32 a);
void svcCloseHandle(Handle a);
Result svcCreateMutex(Handle* mutex, bool initialLocked);
Result svcCreateThread(Handle* a, int(*b)(void*), void* c);
Result svcReleaseMutex(Handle mutex);
void svcSleepThread(u64 a);
void svcWaitSynchronization(Handle a, u64 b);
u64 svcGetSystemTick();

void FSFILE_Close(Handle a);
int linearSpaceFree();

#define FIXME_HACK() { assert(false); }

static void irrstExit() FIXME_HACK()
static void hidExit() FIXME_HACK()
static void fsExit() FIXME_HACK()
static void gfxExit() FIXME_HACK()
static void aptExit() FIXME_HACK()
static void srvExit() FIXME_HACK()
static void svcExitThread() FIXME_HACK()

