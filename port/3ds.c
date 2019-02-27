#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))

#include <assert.h>
#include <stdlib.h>

#include "3ds.h"

SDL_GameController* controller = NULL;

int keys = 0;
int last_keys = 0;

float light_xyzw[4];

uint8_t sub_buffer[320*240 * 3];

static int handle_count = 0;
static void* handles[1000];
static const int handle_base = 1337000;

void* create_handle(Handle* handle, size_t size) {
  assert(handle_count < ARRAY_SIZE(handles));
  void* data = malloc(size);
  handles[handle_count] = data;
  *handle = handle_base + handle_count++;
  return data;
}

void* get_handle(Handle handle) {
  return handles[handle - handle_base];
}

void destroy_handle(Handle handle) {
  free(handles[handle - handle_base]);
  handles[handle - handle_base] = NULL;
}









#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

static void display_cb() {}

void srvInit() {}
void aptInit() {}
void gfxInit() {

  int argc = 1;
  char* argv[1] = { "GLUT" };
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
  //glutInitWindowSize(400, 2 * 240);
  glutInitWindowSize(640, 480);
  glutCreateWindow("GLUT");
  glutDisplayFunc(display_cb);

  GLenum err = glewInit();
  if (GLEW_OK != err) {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
  }

  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER);

  controller = SDL_GameControllerOpen(0);
  printf("'%s'\n", SDL_GameControllerName(controller));

  //FIXME: SDL_CreateWindow(); ?
  
}
void fsInit() {}
void hidInit(bool x) {
  //FIXME: GLUT keyboard stuff?
}
void irrstInit(bool x) {}
void gfxSet3D(bool x) {}

void* SHDR_ParseSHBIN(u32* a, size_t b) {
  return (void*)0xDEADBEEF; // Must be non-null
}
u32 SHDR_GetUniformRegister(void* a, char* b, int c) {
  //printf("Looking for uniform '%s' %d\n", b, c);
  return (u32)b; //FIXME: We should strdup here, but keep existing names in a list
}
void SHDR_UseProgram(void* a, int b) {
  //printf("Switching shader program\n");
}

void gspWaitForEvent(int a, int b) {
  assert(a == GSPEVENT_VBlank0);
  assert(b == true);
}
void gspWaitForP3D() {}
void gspWaitForPPF() {}
void gspWaitForPSC0() {}

void GX_SetMemoryFill(u32* a, ...) {
  //FIXME: GX_SetDisplayTransfer(gxCmdBuf, (u32*)gpuOut, 0x019001E0, u32* addr, 0x019001E0, 0x01001000);
  //FIXME: glClear?
  glClearColor(0x68/255.0f, 0xB0/255.0f, 0xD8/255.0f, 1.0f); //FIXME: Use correct color
  glClearDepth(0.0f);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GX_SetDisplayTransfer(void* a, u32* b, u32 c, u32* d, u32 e, u32 f) {
  //FIXME: Implement
}

void GPU_DepthRange(float a, float b) {
  //FIXME: Can we just stick to GL defaults?
  assert(a == -1.0f);
  assert(b == 0.0f);
}
void GPU_SetFaceCulling(int a) {
  switch(a) {
  case GPU_CULL_BACK_CCW:
    glFrontFace(GL_CCW);
    break;
  default:
    assert(false);
    break;
  }
}
void GPU_SetStencilTest(bool a, int b, uint8_t c, uint8_t d, uint8_t e) {
  //FIXME: Implement using glStencilMaskSeparate, glStencilFuncSeparate
  assert(a == false);
  assert(b == GPU_ALWAYS);
  assert(e == 0x00);
//FIXME:  glStencilFunc(GL_ALWAYS, c, d);
}
void GPU_SetViewport(u32* a, u32* b, int c, int d, int e, int f) {
  //FIXME: Respect a and b?
  printf("Viewport at %d,%d is %dx%d\n", c, d, e, f);
  glViewport(0, 0, 640, 480);
}
void GPU_SetStencilOp(int a, int b, int c) { 
  assert(a == GPU_KEEP);
  assert(b == GPU_KEEP);
  assert(c == GPU_KEEP);
//FIXME:  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
}
void GPU_SetBlendingColor(int a, int b, int c, int d) {
  //FIXME: Implement
  assert(a == 0);
  assert(b == 0);
  assert(c == 0);
  assert(d == 0);
}
void GPU_FinishDrawing() {
  glFinish();
}

void GPUCMD_Finalize() {}
void GPUCMD_GetBuffer(void* a, void* b, u32* c) {}
void GPUCMD_FlushAndRun(void* a) {}



// Hacks:

void aptCloseSession() {}
void aptOpenSession() {}
bool aptMainLoop() {

  // Do event processing
  for(int i = 0; i < 30; i++) {
    glutMainLoopEvent();
  }

  return true;
}

Result APT_SetAppCpuTimeLimit(void* a, int b) { return 0; }

void FSFILE_Close(Handle a) {
  assert(false);
}
Result FSFILE_GetSize(Handle a, u64* b) {
  FILE** file = get_handle(a);
  //fseek(*file, 0, SEEK_END); //FIXME: Is this necessary?
  *b = ftell(*file);
  return 0;
}
Result FSFILE_Read(Handle a, u32* b, u32 c, void* d, u32 e) {
  FILE** file = get_handle(a);
  fseek(*file, c, SEEK_SET);
  *b = fread(d, 1, e, *file);
  return 0;
}
Result FSFILE_Write(Handle a, u32* b, u32 c, const void* d, u32 e, u32 f) {
  assert(f == FS_WRITE_FLUSH);

  FILE** file = get_handle(a);
  fseek(*file, c, SEEK_SET);
  *b = fwrite(d, 1, e, *file);
  assert(*b == e);
  return 0;
}

char* FS_makePath(int a, char* b) {
  //FIXME: Check what this does
  assert(a == PATH_CHAR);
  printf("Path: '%s'\n", b);
  return b;
}

Result FSUSER_OpenArchive(void* a, void* b) {
  //FIXME!
  return 0;
}
Result FSUSER_OpenFile(void* a, Handle* b, FS_archive c, char* d, int e, int f) {
  char buf[2048];
  sprintf(buf, "./store/%s", d);
  const char* mode = (e & FS_OPEN_CREATE) ? "wb" : "rb";
  FILE* tmp = fopen(buf, mode);
  printf("Opened '%s' in mode '%s': %p\n", buf, mode, tmp);
  if (tmp == NULL) {
    *b = -1;
    return 1;
  }
  FILE** file = create_handle(b, sizeof(FILE*));
  *file = tmp;
  printf("Handle is %d\n", *b);
  return 0;
}

void* gfxGetFramebuffer(int a, int b, u16* c, u16* d) {
  //gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL)
  if (a == GFX_BOTTOM) {
    assert(b == GFX_BOTTOM);
    if (c) { *c = 320; }
    if (d) { *d = 240; }
    return sub_buffer;
  }
  assert(c == NULL);
  assert(d == NULL);
  //FIXME: gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
  return NULL;
}
void gfxSwapBuffersGpu() {
  
#if 1
  GLint prev;
  glGetIntegerv(GL_TEXTURE_BINDING_2D, &prev);
  

  //FIXME: Get current texture unit
  static GLint fb = -1;

  if (fb == -1) {
    glGenTextures(1, &fb);
  }

  glDisable(GL_LIGHTING);
  glDisable(GL_DEPTH_TEST);

  glBindTexture(GL_TEXTURE_2D, fb);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 320, 240, 0, GL_BGR, GL_UNSIGNED_BYTE, sub_buffer);

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0f, 1.0f, 1.0f, 0.0f);

  float w = 320.0f / 640.0f;
  float h = 240.0f / 480.0f;

  float x = 1.0f - w;
  float y = 1.0f - h;

  glBegin(GL_QUADS);
  glTexCoord2f(0.5f, 1.0f);
  glVertex2f(x, y);
  glTexCoord2f(0.5f, 0.0f);
  glVertex2f(x + w, y);
  glTexCoord2f(0.0f, 0.0f);
  glVertex2f(x + w, y + h);
  glTexCoord2f(0.0f, 1.0f);
  glVertex2f(x, y + h);
  glEnd();

  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glBindTexture(GL_TEXTURE_2D, prev);

  glFinish();
#endif

  glutSwapBuffers();
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//void GPUCMD_SetBuffer(int a, ...) FIXME_HACK()
void GPUCMD_SetBufferOffset(int a) {}
//void GPUCMD_AddSingleParam(int a, ...) FIXME_HACK()

void GPU_Reset(u32* a, ...) {}
void GPU_Init(void* a) {

  // Bind out texture unit emulation
  int tex0;
  glGenTextures(1, &tex0);
  glBindTexture(GL_TEXTURE_2D, tex0);

}
void GPU_SetAlphaBlending(int a, int b, int c, int d, int e, int f) {
  assert(a == GPU_BLEND_ADD);
  assert(b == a);
  glBlendEquation(GL_FUNC_ADD);

  assert(c == GPU_SRC_ALPHA);
  assert(d == GPU_ONE_MINUS_SRC_ALPHA);
  assert(e == GPU_SRC_ALPHA);
  assert(f == GPU_ONE_MINUS_SRC_ALPHA);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GPU_SetAlphaTest(bool a, int b, uint8_t c) {
  //FIXME: Implement
  assert(a == false);
  assert(b == GPU_ALWAYS);
  assert(c == 0x00);
}
void GPU_SetAttributeBuffers(int a, ...) {
  //FIXME: Implement

  //FIXME: GPU_SetAttributeBuffers(3, (u32*)osConvertVirtToPhys((u32)texData),
//			GPU_ATTRIBFMT(0, 3, GPU_FLOAT)|GPU_ATTRIBFMT(1, 2, GPU_FLOAT)|GPU_ATTRIBFMT(2, 3, GPU_FLOAT),
//			0xFFC, 0x210, 1, (u32[]){0x00000000}, (u64[]){0x210}, (u8[]){3});  

#warning Missing GPU_SetAttributeBuffers
  //FIXME_HACK()
}
void GPU_SetDepthTestAndWriteMask(int a, int b, int c) {
  //FIXME: Implement
  assert(a == true);
  glEnable(GL_DEPTH_TEST);

  assert(b == GPU_GREATER);
  glDepthFunc(GL_GREATER);

  assert(c == GPU_WRITE_ALL); //FIXME: glDepthMask?
}
void GPU_SetTexEnv(int a, int b, int c, int d, int e, int f, int g, u32 h) {
/*
GPU_SetTexEnv(0, 
84			GPU_TEVSOURCES(GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR), 
85			GPU_TEVSOURCES(GPU_TEXTURE0, GPU_PRIMARY_COLOR, GPU_PRIMARY_COLOR),
86			GPU_TEVOPERANDS(0,0,0), 
87			GPU_TEVOPERANDS(0,0,0), 
(gdb) list
88			GPU_MODULATE, GPU_MODULATE, 
89			0xFFFFFFFF);
*/
  //FIXME: Implement!
}
void GPU_SetTextureEnable(int a) {
  assert(a == GPU_TEXUNIT0);
  glEnable(GL_TEXTURE_2D);
}
void GPU_SetTexture(int a, u32* b, int width, int height, int filter, int format) {
  assert(a == GPU_TEXUNIT0);
//  assert(filter == (GPU_TEXTURE_MAG_FILTER(GPU_NEAREST)|GPU_TEXTURE_MIN_FILTER(GPU_NEAREST)));
//FIXME: filter also GPU_TEXTURE_MAG_FILTER(GPU_NEAREST)|GPU_TEXTURE_MIN_FILTER(GPU_NEAREST)|GPU_TEXTURE_WRAP_S(GPU_REPEAT)|GPU_TEXTURE_WRAP_T(GPU_REPEAT)
  assert(format == GPU_RGBA8);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, b);
}

void GPU_SetUniform(u32 reg, u32* values, int count) {//FIXME: Implement
  //printf("Setting uniform %d to 0x%08X [%d values]\n", reg, values[0], count);

  float* f = (float*)values;

  // Hack via u32 and SHDR_GetUniformRegister
  char* name = (char*)reg;

  if (!strcmp(name, "projection")) {
    glMatrixMode(GL_PROJECTION);
    assert(count == 4);
    float m[4*4];
    for(int i = 0; i < count; i++) {
      for(int j = 0; j < 4; j++) {
        m[i * 4 + j] = f[i * 4 + (3 - j)];
      }
    }
    glLoadIdentity();
    glMultTransposeMatrixf(m);

#if 1    
    glLoadIdentity();
//    gluPerspective(80.0f, 240.0f/400.0f, 0.01f, 1000.0f); //45.0f, 480.0f / 400.0f, -100.0f, 100.0f);
    gluPerspective(80.0f, 480.0f/640.0f, 0.01f, 1000.0f);
#endif

    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
  } else if (!strcmp(name, "modelview")) {
    glMatrixMode(GL_MODELVIEW);
    assert(count == 4);
    float m[4*4];
    for(int i = 0; i < count; i++) {
      for(int j = 0; j < 4; j++) {
        m[i * 4 + j] = f[i * 4 + (3 - j)];
      }
    }
    glLoadIdentity();
    glMultTransposeMatrixf(m);
  } else if (!strcmp(name, "lightAmbient")) {
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    float white[4] = {f[0], f[0], f[0], 1.0f};
    float rgba[4] = { f[3], f[2], f[1], 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, rgba);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
  } else if (!strcmp(name, "lightDirection")) {
    light_xyzw[0] = f[3];
    light_xyzw[1] = f[2];
    light_xyzw[2] = f[1];
  } else {
    printf("Unsupported shader uniform '%s'\n", name);
  }

}

void GPU_DrawArrayDirectly(GPU_Primitive_t primitive, u8* data, u32 n) {
  assert(primitive == GPU_TRIANGLES);

  glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 0, -1, "Draw");

  // Emulate shader
/*
  r0.xyz = dp3(light_dir.xyz, v2.xyz)
  r0.xyz = max(0.0,  r0.xyz)
  r0.xyz *= light_ambient.w
  o1.xyz = light_ambient.xyz + r0.xyz
  o1.w = 1.0
*/


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

//FIXME: Why is the sky gray here, but white in the original code?

#if 0
  glMaterialfv(GL_BACK, GL_EMISSION, white);
  glColorMaterial(GL_BACK, GL_EMISSION);
#endif

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
//    glLoadIdentity();
#if 0
  light_xyzw[0] = 0.0f;
  light_xyzw[1] = 1.0f;
  light_xyzw[2] = 0.0f;
#endif
  light_xyzw[3] = 0.0f;
  glLightfv(GL_LIGHT0, GL_POSITION, light_xyzw);
//  printf("Light dir: %f, %f, %f\n", light_xyzw[0], light_xyzw[1], light_xyzw[2]);
  glPopMatrix();

#if 1
  //FIXME: Disable this hack
  {
    glDepthRange(1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
  }
#endif

  typedef struct {
    float x, y, z;
    float u, v;
    float nx, ny, nz;
  } Vertex;
  const Vertex* vertices = (const Vertex*)data;

#if 0
  glPointSize(10.0f);
  glBegin(GL_POINTS);
  glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3f(0.0, 0.0, 0.0);
  glEnd();
#endif

#if 0
GLdouble model[4*4];
GLdouble proj[4*4];
GLint view[4];
glGetDoublev(GL_MODELVIEW_MATRIX, model);
glGetDoublev(GL_PROJECTION_MATRIX, proj);
glGetIntegerv(GL_VIEWPORT, view);
GLdouble winX, winY, winZ;
GLint ret = gluProject(0,0,0,  model, proj, view, &winX,&winY,&winZ);
if (ret == GLU_TRUE) {
  printf("%f %f %f\n", winX, winY, winZ);
}
#endif

  glColor3f(1.0f, 1.0f, 1.0f);
  glBegin(GL_TRIANGLES);

  for(int i = 0; i < n; i++) {
    const Vertex* v = &vertices[i];
    glNormal3f(v->nx, v->ny, v->nz);
    glTexCoord2f(v->u, 1.0f - v->v);
    glVertex3f(v->x, v->y, v->z);
  }

  glEnd();

  glPopDebugGroup();
}

void GSPGPU_FlushDataCache(void* a, u8* b, size_t c) {
  //FIXME: Can this be a nop?
}

void hidScanInput() {

  //FIXME: Update xpad or something
  SDL_GameControllerUpdate();

  // Update result for hidKeysDown?
  last_keys = keys;
  keys = 0;

  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP)) {
    keys |= KEY_DUP; // Fly
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT)) {
    keys |= KEY_DLEFT; // ?
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
    keys |= KEY_DDOWN; // ?
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
    keys |= KEY_DRIGHT; // Block selection
  }

  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A)) {
    keys |= KEY_A; // ?
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B)) {
    keys |= KEY_B; // ?
  }

  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X)) {
    keys |= KEY_ZL; // ?
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y)) {
    keys |= KEY_ZR; // ?
  }

  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START)) {
    keys |= KEY_START; // ?
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK)) {
    keys |= KEY_SELECT; // ?
  }

  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
    keys |= KEY_L; // Jump
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
    keys |= KEY_R; // Place block
  }
  if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK)) {
    keys |= KEY_TOUCH; // Rotate view
  }
  
}
void hidCircleRead(circlePosition* a) {
  //SDL_GameControllerUpdate();
  int16_t deadzone = 0x4000;
  int16_t shift = 0x100;
  a->dx = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
  a->dy = 0xFFFF ^ SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
  if (abs(a->dx) < deadzone) { a->dx = 0; }
  if (abs(a->dy) < deadzone) { a->dy = 0; }
  a->dx /= shift;
  a->dy /= shift;
}
void hidCstickRead(circlePosition* a) {
  int16_t deadzone = 0x4000;
  int16_t shift = 0x100;
  a->dx = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX);
  a->dy = 0xFFFF ^ SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY);
  if (abs(a->dx) < deadzone) { a->dx = 0; }
  if (abs(a->dy) < deadzone) { a->dy = 0; }
  a->dx /= shift;
  a->dy /= shift;
}
int hidKeysHeld() {
  return keys;
}
int hidKeysDown() {
  int changed = keys ^ last_keys;
  int down = changed & ~keys;
  return down;
}
void hidTouchRead(touchPosition* a) {
  //FIXME: Get mouse coordinates
  a->px = 0;
  a->py = 0;
#if 0
  a->px = 30000 + sinf(((int)(t * 1000) % 1000) / 1000.0f) * 30000;
  a->py = 30000 + cosf(t) * 30000;
#endif
}

int keysDown() {
  return hidKeysDown(); //FIXME: What's the difference?
}
int keysHeld() {
  return hidKeysHeld(); //FIXME: What's the difference?
}

void* linearAlloc(u32 a) {
  //FIXME: Might be relevant for platforms like Xbox
  return malloc(a);
}
void linearFree(void* a) {
  //FIXME: Might be relevant for platforms like Xbox
  free(a);
}
void* linearMemAlign(u32 a, u32 b) {
  uintptr_t addr = (uintptr_t)malloc(a * 2); //FIXME: Only allow 32 bit addresses
  addr += (b - (addr % b)) % b;
  assert((addr % b) == 0);
  return (void*)addr;
}
int linearSpaceFree() {
  assert(false);
}

u32 osConvertVirtToPhys(u32 a) {
  //FIXME: Might be relevant for platforms like Xbox
  return a;
}

void svcCloseHandle(Handle a) {
  //FIXME: Ref-counting maybe?
  //destroy_handle(a);
}
Result svcCreateMutex(Handle* mutex, bool initialLocked) {
  assert(initialLocked == false);
  mtx_t* m = create_handle(mutex, sizeof(mtx_t));
  mtx_init(m, mtx_plain);
  return 0;
}
Result svcCreateThread(Handle* a, int(*b)(void*), void* c) {
  thrd_t* t = create_handle(a, sizeof(thrd_t));
  thrd_create(t, b, c);
}
Result svcReleaseMutex(Handle mutex) {
  mtx_t* m = get_handle(mutex);
  mtx_unlock(m);
}
void svcSleepThread(u64 a) {
  //FIXME: Handle remaining time for signals
  struct timespec ts = { .tv_nsec = a };
  //printf("Sleep!\n");
  while(thrd_sleep(&ts, &ts) != 0);
}
void svcWaitSynchronization(Handle a, u64 b) {
  mtx_t* m = get_handle(a);
  assert(b == U64_MAX); //FIXME: timedlock
  mtx_lock(m);
}
u64 svcGetSystemTick() {
  u64 t = SDL_GetTicks() * 268123480ULL / 1000ULL;
  return t;
}

