#include "stdafx.h"
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#pragma comment(lib, "D3D10_1.lib")
#pragma comment(lib, "DXGI.lib")
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
///////////////**************new**************////////////////////
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
///////////////**************new**************////////////////////

#include <windows.h>
#include "Resource.h"
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <D3D10_1.h>
#include <DXGI.h>
#include <D2D1.h>
#include <sstream>
#include <dwrite.h>
///////////////**************new**************////////////////////
#include <dinput.h>
///////////////**************new**************////////////////////
///////////////**************new**************////////////////////
#include <vector>
#include <fstream>
#include <istream>
///////////////**************new**************////////////////////
//ȫ��������
IDXGISwapChain* SwapChain;
ID3D11Device* d3d11Device;
ID3D11DeviceContext* d3d11DevCon;
ID3D11RenderTargetView* renderTargetView;

//��������
//ID3D11Buffer* squareIndexBuffer;

//���ֵ-20170927
ID3D11DepthStencilView* depthStencilView;
ID3D11Texture2D* depthStencilBuffer;

//��ɫ��
//ID3D11Buffer* squareVertBuffer;
ID3D11VertexShader* VS;
ID3D11PixelShader* PS;
ID3D11PixelShader* D2D_PS;
ID3D10Blob* D2D_PS_Buffer;
ID3D10Blob* VS_Buffer;
ID3D10Blob* PS_Buffer;
ID3D11InputLayout* vertLayout;

///
ID3D11Buffer* cbPerObjectBuffer;
ID3D11BlendState* d2dTransparency;
ID3D11RasterizerState* CCWcullMode;
ID3D11RasterizerState* CWcullMode;
//ID3D11ShaderResourceView* CubesTexture;
ID3D11SamplerState* CubesTexSamplerState;

ID3D11Buffer* cbPerFrameBuffer;

ID3D10Device1 *d3d101Device;
IDXGIKeyedMutex *keyedMutex11;
IDXGIKeyedMutex *keyedMutex10;
ID2D1RenderTarget *D2DRenderTarget;
ID2D1SolidColorBrush *Brush;
ID3D11Texture2D *BackBuffer11;
ID3D11Texture2D *sharedTex11;
ID3D11Buffer *d2dVertBuffer;
ID3D11Buffer *d2dIndexBuffer;
ID3D11ShaderResourceView *d2dTexture;
IDWriteFactory *DWriteFactory;
IDWriteTextFormat *TextFormat;
///////////////**************new**************////////////////////
IDirectInputDevice8* DIKeyboard;
IDirectInputDevice8* DIMouse;
///////////////**************new**************////////////////////
ID3D11Buffer* sphereIndexBuffer;
ID3D11Buffer* sphereVertBuffer;

ID3D11VertexShader* SKYMAP_VS;
ID3D11PixelShader* SKYMAP_PS;
ID3D10Blob* SKYMAP_VS_Buffer;
ID3D10Blob* SKYMAP_PS_Buffer;

ID3D11ShaderResourceView* smrv;

ID3D11DepthStencilState* DSLessEqual;
ID3D11RasterizerState* RSCullNone;
///////////////**************new**************////////////////////
ID3D11BlendState* Transparency;
//���������ÿ�������ص�������Ҫ���Լ��ļ�
ID3D11Buffer* meshVertBuff;
ID3D11Buffer* meshIndexBuff;
XMMATRIX meshWorld;
int meshSubsets = 0;
std::vector<int> meshSubsetIndexStart;
std::vector<int> meshSubsetTexture;


//�����Ͳ��ʱ������������е�����ļ���
std::vector<ID3D11ShaderResourceView*> meshSRV;
std::vector<std::wstring> textureNameArray;
///////////////**************new**************////////////////////
std::wstring printText;
/////
LPCTSTR WndClassName = L"firstwindow";
HWND hwnd = NULL;
HRESULT hr;

const int Width = 1920; //���ÿ�
const int Height = 1200; // ���ø�

///////////////**************new**************////////////////////
DIMOUSESTATE mouseLastState;
LPDIRECTINPUT8 DirectInput;

float rotx = 0;
float rotz = 0;
float scaleX = 1.0f;
float scaleY = 1.0f;

XMMATRIX Rotationx;
//XMMATRIX Rotationy;
XMMATRIX Rotationz;
XMMATRIX Rotationy;
///////////////**************new**************////////////////////
///�ĸ��ռ��Լ��������
XMMATRIX WVP;
//������
//XMMATRIX cube1World;
//XMMATRIX cube2World;
//
//XMMATRIX World;
XMMATRIX camView;
XMMATRIX camProjection;

XMMATRIX d2dWorld;
XMVECTOR camPosition;
XMVECTOR camTarget;
XMVECTOR camUp;
///////////////**************new**************////////////////////
XMVECTOR DefaultForward = XMVectorSet(0.0f,0.0f,1.0f, 0.0f);
XMVECTOR DefaultRight = XMVectorSet(1.0f,0.0f,0.0f, 0.0f);
XMVECTOR camForward = XMVectorSet(0.0f,0.0f,1.0f, 0.0f);
XMVECTOR camRight = XMVectorSet(1.0f,0.0f,0.0f, 0.0f);

XMMATRIX camRotationMatrix;
//XMMATRIX groundWorld;

float moveLeftRight = 0.0f;
float moveBackForward = 0.0f;

float camYaw = 0.0f;
float camPitch = 0.0f;
///////////////**************new**************////////////////////
int NumSphereVertices;
int NumSphereFaces;

XMMATRIX sphereWorld;
///////////////**************new**************////////////////////
XMMATRIX Rotation;
XMMATRIX Scale;
XMMATRIX Translation;

float rot = 0.01f;

///////////////**************new**************////////////////////
double countsPerSecond = 0.0;
__int64 CounterStart = 0;

int frameCount = 0;
int fps = 0;

__int64 frameTimeOld = 0;
double frameTime;
///////////////**************new**************////////////////////
//Function Prototypes//
bool InitializeDirect3d11App(HINSTANCE hInstance);
void CleanUp();
bool InitScene();
void DrawScene();
bool InitD2D_D3D101_DWrite(IDXGIAdapter1 *Adapter);
void InitD2DScreenTexture();
///////////////**************new**************////////////////////
void UpdateScene(double time);
///////////////**************new**************////////////////////
void UpdateCamera();

void RenderText(std::wstring text, int inInt);
//void RenderText(std::wstring text);

void StartTimer();
double GetTime();
double GetFrameTime();


// ��ʼ������
bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed);

//��ʼ����Ϣѭ������
int messageloop();
//��ʼ�����ڻص����̡�Windows API���¼������͵ı��ģ�͡��ڸú����в���Windows��Ϣ������һ���������£�Ҳ���¼����Լ�����������̡�
///////////////**************new**************////////////////////
bool InitDirectInput(HINSTANCE hInstance);
void DetectInput(double time);
///////////////**************new**************////////////////////
void CreateSphere(int LatLines, int LongLines);

LRESULT CALLBACK WndProc(HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam);

///new
//����Ч����������Ľṹ��
struct cbPerObject
{
	XMMATRIX WVP;
	XMMATRIX World;

	///////////////**************new**************////////////////////
	//����������ɫ��
	XMFLOAT4 difColor;
	BOOL hasTexture;
	///////////////**************new**************////////////////////
	//Because of HLSL structure packing, we will use windows BOOL
	//instead of bool because HLSL packs things into 4 bytes, and
	//bool is only one byte, where BOOL is 4 bytes
	BOOL hasNormMap;
	///////////////**************new**************////////////////////
};

cbPerObject cbPerObj;

///////////////**************new**************////////////////////
//�������ʽṹ��
struct SurfaceMaterial
{
	std::wstring matName;
	XMFLOAT4 difColor;
	int texArrayIndex;
	///////////////**************new**************////////////////////
	int normMapTexArrayIndex;
	bool hasNormMap;
	///////////////**************new**************////////////////////
	bool hasTexture;
	bool transparent;
};

std::vector<SurfaceMaterial> material;

//�Դ���surfaceMaterial�ṹ��󣬶��庯��LoadObjModel
bool LoadObjModel(std::wstring filename,			//.obj filename
	ID3D11Buffer** vertBuff,					//mesh vertex buffer
	ID3D11Buffer** indexBuff,					//mesh index buffer
	std::vector<int>& subsetIndexStart,			//start index of each subset
	std::vector<int>& subsetMaterialArray,		//index value of material for each subset
	std::vector<SurfaceMaterial>& material,		//vector of material structures
	int& subsetCount,							//Number of subsets in mesh
	bool isRHCoordSys,							//true if model was created in right hand coord system
    bool computeNormals);                        //true to compute the normals, false to use the files normals

///////////////**************new**************////////////////////
struct Light
{
	Light()
	{
		ZeroMemory(this, sizeof(Light));
	}
	XMFLOAT3 pos;
	float range;
	XMFLOAT3 dir;
	float cone;
	XMFLOAT3 att;
	float pad2;
	XMFLOAT4 ambient;
	XMFLOAT4 diffuse;

};
Light light;

struct cbPerFrame
{
	Light light;
};

cbPerFrame constbuffPerFrame;


//����ṹ���Լ����㲼�֣����벼�֣�

struct Vertex
{
	Vertex(){}
	Vertex(float x, float y, float z,
		float u, float v,
		float nx, float ny, float nz,
		float tx, float ty, float tz)
		: pos(x,y,z), texCoord(u, v), normal(nx, ny, nz),
		tangent(tx, ty, tz){}
	XMFLOAT3 pos;
	XMFLOAT2 texCoord;
	XMFLOAT3 normal;
	///////////////**************new**************////////////////////
	XMFLOAT3 tangent;
	XMFLOAT3 biTangent;
///////////////**************new**************////////////////////
    // ���ᴫ����ɫ����
    int StartWeight;
    int WeightCount;
///////////////**************new**************////////////////////
};

D3D11_INPUT_ELEMENT_DESC layout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",	 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
	///////////////**************new**************////////////////////
	{ "TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0}
	///////////////**************new**************////////////////////
};
UINT numElements = ARRAYSIZE(layout);

///////////////**************new**************////////////////////
struct Joint
{
    std::wstring name;
    int parentID;

    XMFLOAT3 pos;
    XMFLOAT4 orientation;
};

///////////////**************new**************////////////////////
struct BoundingBox
{
    XMFLOAT3 min;
    XMFLOAT3 max;
};

struct FrameData
{
    int frameID;
    std::vector<float> frameData;
};
struct AnimJointInfo
{
    std::wstring name;
    int parentID;

    int flags;
    int startIndex;
};

struct ModelAnimation
{
    int numFrames;
    int numJoints;
    int frameRate;
    int numAnimatedComponents;

    float frameTime;
    float totalAnimTime;
    float currAnimTime;

    std::vector<AnimJointInfo> jointInfo;
    std::vector<BoundingBox> frameBounds;
    std::vector<Joint>    baseFrameJoints;
    std::vector<FrameData>    frameData;
    std::vector<std::vector<Joint>> frameSkeleton;
};
///////////////**************new**************////////////////////

struct Weight
{
    int jointID;
    float bias;
    XMFLOAT3 pos;
    ///////////////**************new**************////////////////////
    XMFLOAT3 normal;
    ///////////////**************new**************////////////////////
};

struct ModelSubset
{
    int texArrayIndex;
    int numTriangles;

    std::vector<Vertex> vertices;
    std::vector<XMFLOAT3> jointSpaceNormals;
    std::vector<DWORD> indices;
    std::vector<Weight> weights;

    std::vector<XMFLOAT3> positions;

    ID3D11Buffer* vertBuff; 
    ID3D11Buffer* indexBuff;
};

struct Model3D
{
    int numSubsets;
    int numJoints;

    std::vector<Joint> joints;
    std::vector<ModelSubset> subsets;
    ///////////////**************new**************////////////////////
    std::vector<ModelAnimation> animations;
    ///////////////**************new**************////////////////////
};

XMMATRIX smilesWorld;
Model3D NewMD5Model;

//LoadMD5Model() function prototype
bool LoadMD5Model(std::wstring filename,
    Model3D& MD5Model,
    std::vector<ID3D11ShaderResourceView*>& shaderResourceViewArray,
    std::vector<std::wstring> texFileNameArray);
///////////////**************new**************////////////////////
bool LoadMD5Anim(std::wstring filename,    Model3D& MD5Model);

void UpdateMD5Model(Model3D& MD5Model, float deltaTime, int animation);
//������������Ӧ�ó�����hInstance,ǰһ��Ӧ�ó�����hPrevInstance����������������������lpCmdLine�Լ�������ʾ��ʽ��nShowCmd
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	//������ע�ᴰ��
	if (!InitializeWindow(hInstance, nShowCmd, Width, Height, true))
	{
		MessageBox(0, L"Window Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	/////new
	if (!InitializeDirect3d11App(hInstance)) // ��ʼ��D3D
	{
		MessageBox(0, L"Direct3D Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	if(!InitScene())	//Initialize our scene
	{
		MessageBox(0, L"Scene Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}

	///////////////**************new**************////////////////////
	if(!InitDirectInput(hInstance))
	{
		MessageBox(0, L"Direct Input Initialization - Failed",
			L"Error", MB_OK);
		return 0;
	}
	///////////////**************new**************////////////////////

	messageloop();
	CleanUp();
	//ReleaseObjects();

	return 0;
}
// windowed ��Ϊtrue��Ϊ����ģʽ��ʾ����Ϊfalse��Ϊȫ��ģʽ��ʾ
bool InitializeWindow(HINSTANCE hInstance,
	int ShowWnd,
	int width, int height,
	bool windowed)
{
    typedef struct _WNDCLASS {
        UINT cbSize;
        UINT style;
        WNDPROC lpfnWndProc;
        int cbClsExtra;
        int cbWndExtra;
        HANDLE hInstance;
        HICON hIcon;
        HCURSOR hCursor;
        HBRUSH hbrBackground;
        LPCTSTR lpszMenuName;
        LPCTSTR lpszClassName;
    } WNDCLASS;

	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX); //window��Ĵ�С
	/********windows����
	*CS_CLASSDC һ��ʹ�ø��ഴ���������д��ڼ乲�����豸������
	*CS_DBLCLKS �ڴ�����ʹ��˫������
	*CS_HREDRAW �����ڵĿ����иı���ߴ���ˮƽ���ƶ������ڽ���ˢ��
	*CS_NOCLOSE ���ڲ˵��Ͻ�ֹ�ر�ѡ��
	*CS_OWNDC   Ϊÿ�����ڴ����Լ����豸�����ġ�������CS_CLASSDC�෴
	*CS_PARENTDC ������ô������Ӵ��ڵļ����ı��ε������ڣ��������Ӵ����ܹ��ڸ������ϻ滭
	*CS_VERDRAW ���ڴ��ڵĸ߶Ȼ򴰿��ڴ�ֱ�������ƶ����ڻ��ػ�
	**/
	wc.style = CS_HREDRAW | CS_VREDRAW;
	//lpfnWndProc��һ��ָ����������Ϣ������ָ�룬���ô��ڴ��������ĺ�����WndProc
	wc.lpfnWndProc = WndProc;
	//cbClsExtra��WNDCLASSEX֮�����������ֽ���
	wc.cbClsExtra = NULL;
	//cbWndExtraָ������ʵ��֮����������ֽ���
	wc.cbWndExtra = NULL;
	//��ǰ����Ӧ�ó���ľ����ͨ��������GetModuleHandle()������һ����������NULL�ɻ�ȡ��ǰ����Ӧ�ó���
	wc.hInstance = hInstance;

	//hIcon����ָ�����ڱ��������Ͻǵ�ͼ�ꡣ������һЩ��׼ͼ�꣺
	/*
	*IDI_APPLICATION Ĭ��Ӧ�ó���ͼ��
	*IDI_HAND ����״��ͼ��
	*IDI_EXCLAMATION ��̾��ͼ��
	*IDI_INFORMATION �Ǻ�ͼ��
	*IDI_QUESTION �ʺ�ͼ��
	*IDI_WINLOGO ��ʹ�õ���XP����Ĭ��Ӧ�ó���ͼ�꣬�����Ǵ���logo
	*/
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	/*������ͼ��
	*IDC_APPSTARTING ��׼��ͷ�Լ�С��ɳ©���
	*IDC_ARROW ��׼��ͷ���
	*IDC_CROSS ʮ���߹��
	*IDC_HAND ���͹��
	*IDC_NO б��Ȧ���
	*IDC_WAIT ɳ©���
	*/
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//hbrBackground��һ��ˢ�ӵľ������ʹ�ñ�����ɫ��
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//���ӵ����ڵĲ˵����֣�����Ҫ�Ļ�����ΪNULL
	wc.lpszMenuName = NULL;
	//�����������
	wc.lpszClassName = WndClassName;
	//ָ����������ͼ�꣬ʹ�������IDI��ͼ��
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//ע���ࡣ��ʧ�������һ���������ɹ����������������
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Error registering class",
			L"Error", MB_OK | MB_ICONERROR);
		return 1;
	}
	//��������
	hwnd = CreateWindowEx(
		NULL, 
		WndClassName, 
		L"model md5anim",
		WS_OVERLAPPEDWINDOW, 
        CW_USEDEFAULT, CW_USEDEFAULT,
        width, height,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hwnd)
    {
        MessageBox(NULL, L"Error creating window",
            L"Error", MB_OK | MB_ICONERROR);
        return 1;
	}

	//BOOL ShowWindow(HWND hWnd, int nCmdShow);
	//BOOL UpdateWindow(HWND hWnd);

	ShowWindow(hwnd, ShowWnd);
	UpdateWindow(hwnd);// ����WM_PAINT��Ϣ�����ڹ��̣������ڿͻ���û���κζ���Ҫ��ʾ���򲻷�����Ϣ������true���������е�mainloop��ȥ��

	return true;
}

bool InitializeDirect3d11App(HINSTANCE hInstance)
{
	//��������
	DXGI_MODE_DESC bufferDesc;

	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));

	bufferDesc.Width = Width;
	bufferDesc.Height = Height;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//����������
	DXGI_SWAP_CHAIN_DESC swapChainDesc;

	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hwnd;
	///////////////**************new**************////////////////////
	swapChainDesc.Windowed = true; 
	///////////////**************new**************////////////////////
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	//����DXGI factory��ö���Կ�
	IDXGIFactory1 *DXGIFactory;
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void **)&DXGIFactory);

	//ʹ�õ�һ���Կ�
	IDXGIAdapter1 *Adapter;
	hr = DXGIFactory->EnumAdapters1(0, &Adapter);
	DXGIFactory->Release();

	//����D3D11�豸�ͽ�����
	//hr = D3D11C

	//����������
	D3D11CreateDeviceAndSwapChain(Adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, 
	NULL, NULL,	D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &d3d11Device, NULL, &d3d11DevCon);

	//��ʼ��D2D D3D10.1��DirectWrite
	InitD2D_D3D101_DWrite(Adapter);

	//�ͷ�Adapter�ӿ�
	Adapter->Release();

	//�����󻺳�
	ID3D11Texture2D* BackBuffer;
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

	//������ȾĿ��
	d3d11Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);
	BackBuffer->Release();

	//�������ģ�建��
	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = Width;
	depthStencilDesc.Height = Height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; //�󶨵�OM
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	//�������ģ����ͼ
	d3d11Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	d3d11Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);


	return true;
}

bool InitD2D_D3D101_DWrite(IDXGIAdapter1 *Adapter)
{
	//����D3D101�豸
	hr = D3D10CreateDevice1(Adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_BGRA_SUPPORT,
		D3D10_FEATURE_LEVEL_9_3, D3D10_1_SDK_VERSION, &d3d101Device);

	//��������������D3D101������Ⱦ��
	D3D11_TEXTURE2D_DESC sharedTexDesc;
	ZeroMemory(&sharedTexDesc, sizeof(sharedTexDesc));

	sharedTexDesc.Width = Width;
	sharedTexDesc.Height = Height;
	sharedTexDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;// DXGI_FORMAT_R8G8B8A8_UNORM;// DXGI_FORMAT_B8G8R8A8_UNORM;
	sharedTexDesc.MipLevels = 1;
	sharedTexDesc.ArraySize = 1;
	sharedTexDesc.SampleDesc.Count = 1;
	sharedTexDesc.Usage = D3D11_USAGE_DEFAULT;
	sharedTexDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	sharedTexDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;

	hr = d3d11Device->CreateTexture2D(&sharedTexDesc, NULL, &sharedTex11);
	
	//Ϊ����������ȡkey��������ΪD3D11��
	hr = sharedTex11->QueryInterface(__uuidof(IDXGIKeyedMutex), (void **)&keyedMutex11);

	//��ȡ���������Ҫ��D3D10.1�д򿪹�������
	IDXGIResource *sharedResource10;
	HANDLE sharedHandle10;

	hr = sharedTex11->QueryInterface(__uuidof(IDXGIResource), (void **)&sharedResource10);
	hr = sharedResource10->GetSharedHandle(&sharedHandle10);
	sharedResource10->Release();

	//��D3D10.1��Ϊ���������򿪽���
	IDXGISurface1 *sharedSurface10;
	hr = d3d101Device->OpenSharedResource(sharedHandle10, __uuidof(IDXGISurface1), (void **)(&sharedSurface10));
	hr = sharedSurface10->QueryInterface(__uuidof(IDXGIKeyedMutex), (void **)&keyedMutex10);

	//����D2D factory
	ID2D1Factory *D2DFactory;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void **)&D2DFactory);
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;
	ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));

	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
	renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	hr = D2DFactory->CreateDxgiSurfaceRenderTarget(sharedSurface10, &renderTargetProperties, &D2DRenderTarget);

	sharedSurface10->Release();
	D2DFactory->Release();

	//���������ɫ���ʻ���һЩ����
	hr = D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &Brush);

	//DirectWrite
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), 
	reinterpret_cast<IUnknown **>(&DWriteFactory));
	hr = DWriteFactory->CreateTextFormat(
		L"Script",
		NULL,
        DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		24.0f,
		L"en-us",
        &TextFormat
		);
    hr = TextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    hr = TextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    d3d101Device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_POINTLIST);    
	return true;
}

///////////////**************new**************////////////////////
bool InitDirectInput(HINSTANCE hInstance)
{
    hr = DirectInput8Create(hInstance,
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        (void**)&DirectInput,
        NULL); 

    hr = DirectInput->CreateDevice(GUID_SysKeyboard,
        &DIKeyboard,
        NULL);

    hr = DirectInput->CreateDevice(GUID_SysMouse,
        &DIMouse,
        NULL);

    hr = DIKeyboard->SetDataFormat(&c_dfDIKeyboard);
    hr = DIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

    hr = DIMouse->SetDataFormat(&c_dfDIMouse);
    hr = DIMouse->SetCooperativeLevel(hwnd, DISCL_EXCLUSIVE | DISCL_NOWINKEY | DISCL_FOREGROUND);

    return true;
}

void UpdateCamera()
{
	camRotationMatrix = XMMatrixRotationRollPitchYaw(camPitch, camYaw, 0);
	camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix );
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

    // ����
    //camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
    //camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
    //camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

    // �������
    camRight = XMVector3TransformCoord(DefaultRight, camRotationMatrix);
    camForward = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
    camUp = XMVector3Cross(camForward, camRight);
	camPosition += moveLeftRight*camRight;
	camPosition += moveBackForward*camForward;

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;

	camTarget = camPosition + camTarget;	

	camView = XMMatrixLookAtLH( camPosition, camTarget, camUp );
}
void DetectInput(double time)
{
    DIMOUSESTATE mouseCurrState;

    BYTE keyboardState[256];

    DIKeyboard->Acquire();
    DIMouse->Acquire();

    DIMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouseCurrState);

    DIKeyboard->GetDeviceState(sizeof(keyboardState),(LPVOID)&keyboardState);

    if(keyboardState[DIK_ESCAPE] & 0x80)
        PostMessage(hwnd, WM_DESTROY, 0, 0);

	float speed = 10.0f * time;

	if(keyboardState[DIK_A] & 0x80)
	{
		moveLeftRight -= speed;
	}
	if(keyboardState[DIK_D] & 0x80)
	{
		moveLeftRight += speed;
	}
	if(keyboardState[DIK_W] & 0x80)
	{
		moveBackForward += speed;
	}
	if(keyboardState[DIK_S] & 0x80)
	{
		moveBackForward -= speed;
	}
    ///////////////**************new**************////////////////////
    if(keyboardState[DIK_R] & 0X80)
    {
        float timeFactor = 1.0f;    // ��ͨ���ı��ֵ�����ٻ����ʱ��
        UpdateMD5Model(NewMD5Model, time*timeFactor, 0);
    }
    ///////////////**************new**************////////////////////
	if((mouseCurrState.lX != mouseLastState.lX) || (mouseCurrState.lY != mouseLastState.lY))
	{
		camYaw += mouseLastState.lX * 0.001f;

		camPitch += mouseCurrState.lY * 0.001f;

		mouseLastState = mouseCurrState;
	}

	UpdateCamera();


    return;
}


void CleanUp()
{
	///////////////**************new**************////////////////////
	SwapChain->SetFullscreenState(false, NULL);
	PostMessage(hwnd, WM_DESTROY, 0, 0);
	///////////////**************new**************////////////////////
	SwapChain->Release();
	d3d11Device->Release();
	d3d11DevCon->Release();
	renderTargetView->Release();

	//squareVertBuffer->Release();
	//squareIndexBuffer->Release();

	//triangleVertBuffer->Release();
	VS->Release();
	PS->Release();
	VS_Buffer->Release();
	PS_Buffer->Release();
	vertLayout->Release();

	depthStencilView->Release();
	depthStencilBuffer->Release();

	//
	cbPerObjectBuffer->Release();

	//�ͷŲ��ü�����
//	noCull->Release();
	//�ͷŻ�϶���
//#if 1
	Transparency->Release();
	CCWcullMode->Release();
	CWcullMode->Release();
//#endif	
	//�ͷ��߿�
	//WireFrame->Release();

	d3d101Device->Release();
	keyedMutex11->Release();
	keyedMutex10->Release();
	D2DRenderTarget->Release();
	Brush->Release();
//	BackBuffer11->Release();
	sharedTex11->Release();
	DWriteFactory->Release();
    TextFormat->Release();
	d2dTexture->Release();

	/// new
	cbPerFrameBuffer->Release();
    ///////////////**************new**************////////////////////
    DIKeyboard->Unacquire();
    DIMouse->Unacquire();
    DirectInput->Release();
	sphereIndexBuffer->Release();
	sphereVertBuffer->Release();

	SKYMAP_VS->Release();
	SKYMAP_PS->Release();
	SKYMAP_VS_Buffer->Release();
	SKYMAP_PS_Buffer->Release();

	smrv->Release();

	DSLessEqual->Release();
	RSCullNone->Release();

	///////////////**************new**************////////////////////
	meshVertBuff->Release();
	meshIndexBuff->Release();
    ///////////////**************new**************////////////////////
    for(int i = 0; i < NewMD5Model.numSubsets; i++)
    {
        NewMD5Model.subsets[i].indexBuff->Release();
        NewMD5Model.subsets[i].vertBuff->Release();
    }
}

///////////////**************new**************////////////////////
bool LoadMD5Anim(std::wstring filename,    Model3D& MD5Model)
{    
    ModelAnimation tempAnim;                        // Temp animation to later store in our model's animation array

    std::wifstream fileIn (filename.c_str());        // Open file

    std::wstring checkString;                        // Stores the next string from our file

    if(fileIn)                                        // Check if the file was opened
    {
        while(fileIn)                                // Loop until the end of the file is reached
        {    
            fileIn >> checkString;                    // Get next string from file

            if ( checkString == L"MD5Version" )        // Get MD5 version (this function supports version 10)
            {
                fileIn >> checkString;
                /*MessageBox(0, checkString.c_str(),    //display message
                L"MD5Version", MB_OK);*/
            }
            else if ( checkString == L"commandline" )
            {
                std::getline(fileIn, checkString);    // Ignore the rest of this line
            }
            else if ( checkString == L"numFrames" )
            {
                fileIn >> tempAnim.numFrames;                // Store number of frames in this animation
            }
            else if ( checkString == L"numJoints" )
            {
                fileIn >> tempAnim.numJoints;                // Store number of joints (must match .md5mesh)
            }
            else if ( checkString == L"frameRate" )
            {
                fileIn >> tempAnim.frameRate;                // Store animation's frame rate (frames per second)
            }
            else if ( checkString == L"numAnimatedComponents" )
            {
                fileIn >> tempAnim.numAnimatedComponents;    // Number of components in each frame section
            }
            else if ( checkString == L"hierarchy" )
            {
                fileIn >> checkString;                // Skip opening bracket "{"

                for(int i = 0; i < tempAnim.numJoints; i++)    // Load in each joint
                {
                    AnimJointInfo tempJoint;

                    fileIn >> tempJoint.name;        // Get joints name
                    // Sometimes the names might contain spaces. If that is the case, we need to continue
                    // to read the name until we get to the closing " (quotation marks)
                    if(tempJoint.name[tempJoint.name.size()-1] != '"')
                    {
                        wchar_t checkChar;
                        bool jointNameFound = false;
                        while(!jointNameFound)
                        {
                            checkChar = fileIn.get();

                            if(checkChar == '"')
                                jointNameFound = true;        

                            tempJoint.name += checkChar;                                                            
                        }
                    }

                    // Remove the quotation marks from joints name
                    tempJoint.name.erase(0, 1);
                    tempJoint.name.erase(tempJoint.name.size()-1, 1);

                    fileIn >> tempJoint.parentID;            // Get joints parent ID
                    fileIn >> tempJoint.flags;                // Get flags
                    fileIn >> tempJoint.startIndex;            // Get joints start index

                    // Make sure the joint exists in the model, and the parent ID's match up
                    // because the bind pose (md5mesh) joint hierarchy and the animations (md5anim)
                    // joint hierarchy must match up
                    bool jointMatchFound = false;
                    for(int k = 0; k < MD5Model.numJoints; k++)
                    {
                        if(MD5Model.joints[k].name == tempJoint.name)
                        {
                            if(MD5Model.joints[k].parentID == tempJoint.parentID)
                            {
                                jointMatchFound = true;
                                tempAnim.jointInfo.push_back(tempJoint);
                            }
                        }
                    }
                    if(!jointMatchFound)                    // If the skeleton system does not match up, return false
                        return false;                        // You might want to add an error message here

                    std::getline(fileIn, checkString);        // Skip rest of this line
                }
            }
            else if ( checkString == L"bounds" )            // Load in the AABB for each animation
            {
                fileIn >> checkString;                        // Skip opening bracket "{"

                for(int i = 0; i < tempAnim.numFrames; i++)
                {
                    BoundingBox tempBB;

                    fileIn >> checkString;                    // Skip "("
                    fileIn >> tempBB.min.x >> tempBB.min.z >> tempBB.min.y;
                    fileIn >> checkString >> checkString;    // Skip ") ("
                    fileIn >> tempBB.max.x >> tempBB.max.z >> tempBB.max.y;
                    fileIn >> checkString;                    // Skip ")"

                    tempAnim.frameBounds.push_back(tempBB);
                }
            }            
            else if ( checkString == L"baseframe" )            // This is the default position for the animation
            {                                                // All frames will build their skeletons off this
                fileIn >> checkString;                        // Skip opening bracket "{"

                for(int i = 0; i < tempAnim.numJoints; i++)
                {
                    Joint tempBFJ;

                    fileIn >> checkString;                        // Skip "("
                    fileIn >> tempBFJ.pos.x >> tempBFJ.pos.z >> tempBFJ.pos.y;
                    fileIn >> checkString >> checkString;        // Skip ") ("
                    fileIn >> tempBFJ.orientation.x >> tempBFJ.orientation.z >> tempBFJ.orientation.y;
                    fileIn >> checkString;                        // Skip ")"

                    tempAnim.baseFrameJoints.push_back(tempBFJ);
                }
            }
            else if ( checkString == L"frame" )        // Load in each frames skeleton (the parts of each joint that changed from the base frame)
            {
                FrameData tempFrame;

                fileIn >> tempFrame.frameID;        // Get the frame ID

                fileIn >> checkString;                // Skip opening bracket "{"

                for(int i = 0; i < tempAnim.numAnimatedComponents; i++)
                {
                    float tempData;
                    fileIn >> tempData;                // Get the data

                    tempFrame.frameData.push_back(tempData);
                }

                tempAnim.frameData.push_back(tempFrame);

                ///*** build the frame skeleton ***///
                std::vector<Joint> tempSkeleton;

                for(int i = 0; i < tempAnim.jointInfo.size(); i++)
                {
                    int k = 0;                        // Keep track of position in frameData array

                    // Start the frames joint with the base frame's joint
                    Joint tempFrameJoint = tempAnim.baseFrameJoints[i];

                    tempFrameJoint.parentID = tempAnim.jointInfo[i].parentID;

                    // Notice how I have been flipping y and z. this is because some modeling programs such as
                    // 3ds max (which is what I use) use a right handed coordinate system. Because of this, we
                    // need to flip the y and z axes. If your having problems loading some models, it's possible
                    // the model was created in a left hand coordinate system. in that case, just reflip all the
                    // y and z axes in our md5 mesh and anim loader.
                    if(tempAnim.jointInfo[i].flags & 1)        // pos.x    ( 000001 )
                        tempFrameJoint.pos.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

                    if(tempAnim.jointInfo[i].flags & 2)        // pos.y    ( 000010 )
                        tempFrameJoint.pos.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

                    if(tempAnim.jointInfo[i].flags & 4)        // pos.z    ( 000100 )
                        tempFrameJoint.pos.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

                    if(tempAnim.jointInfo[i].flags & 8)        // orientation.x    ( 001000 )
                        tempFrameJoint.orientation.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

                    if(tempAnim.jointInfo[i].flags & 16)    // orientation.y    ( 010000 )
                        tempFrameJoint.orientation.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];

                    if(tempAnim.jointInfo[i].flags & 32)    // orientation.z    ( 100000 )
                        tempFrameJoint.orientation.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + k++];


                    // Compute the quaternions w
                    float t = 1.0f - ( tempFrameJoint.orientation.x * tempFrameJoint.orientation.x )
                        - ( tempFrameJoint.orientation.y * tempFrameJoint.orientation.y )
                        - ( tempFrameJoint.orientation.z * tempFrameJoint.orientation.z );
                    if ( t < 0.0f )
                    {
                        tempFrameJoint.orientation.w = 0.0f;
                    }
                    else
                    {
                        tempFrameJoint.orientation.w = -sqrtf(t);
                    }

                    // Now, if the upper arm of your skeleton moves, you need to also move the lower part of your arm, and then the hands, and then finally the fingers (possibly weapon or tool too)
                    // This is where joint hierarchy comes in. We start at the top of the hierarchy, and move down to each joints child, rotating and translating them based on their parents rotation
                    // and translation. We can assume that by the time we get to the child, the parent has already been rotated and transformed based of it's parent. We can assume this because
                    // the child should never come before the parent in the files we loaded in.
                    if(tempFrameJoint.parentID >= 0)
                    {
                        Joint parentJoint = tempSkeleton[tempFrameJoint.parentID];

                        // Turn the XMFLOAT3 and 4's into vectors for easier computation
                        XMVECTOR parentJointOrientation = XMVectorSet(parentJoint.orientation.x, parentJoint.orientation.y, parentJoint.orientation.z, parentJoint.orientation.w);
                        XMVECTOR tempJointPos = XMVectorSet(tempFrameJoint.pos.x, tempFrameJoint.pos.y, tempFrameJoint.pos.z, 0.0f);
                        XMVECTOR parentOrientationConjugate = XMVectorSet(-parentJoint.orientation.x, -parentJoint.orientation.y, -parentJoint.orientation.z, parentJoint.orientation.w);

                        // Calculate current joints position relative to its parents position
                        XMFLOAT3 rotatedPos;
                        XMStoreFloat3(&rotatedPos, XMQuaternionMultiply(XMQuaternionMultiply(parentJointOrientation, tempJointPos), parentOrientationConjugate));

                        // Translate the joint to model space by adding the parent joint's pos to it
                        tempFrameJoint.pos.x = rotatedPos.x + parentJoint.pos.x;
                        tempFrameJoint.pos.y = rotatedPos.y + parentJoint.pos.y;
                        tempFrameJoint.pos.z = rotatedPos.z + parentJoint.pos.z;

                        // Currently the joint is oriented in its parent joints space, we now need to orient it in
                        // model space by multiplying the two orientations together (parentOrientation * childOrientation) <- In that order
                        XMVECTOR tempJointOrient = XMVectorSet(tempFrameJoint.orientation.x, tempFrameJoint.orientation.y, tempFrameJoint.orientation.z, tempFrameJoint.orientation.w);
                        tempJointOrient = XMQuaternionMultiply(parentJointOrientation, tempJointOrient);

                        // Normalize the orienation quaternion
                        tempJointOrient = XMQuaternionNormalize(tempJointOrient);

                        XMStoreFloat4(&tempFrameJoint.orientation, tempJointOrient);
                    }

                    // Store the joint into our temporary frame skeleton
                    tempSkeleton.push_back(tempFrameJoint);
                }

                // Push back our newly created frame skeleton into the animation's frameSkeleton array
                tempAnim.frameSkeleton.push_back(tempSkeleton);

                fileIn >> checkString;                // Skip closing bracket "}"
            }
        }

        // Calculate and store some usefull animation data
        tempAnim.frameTime = 1.0f / tempAnim.frameRate;                        // Set the time per frame
        tempAnim.totalAnimTime = tempAnim.numFrames * tempAnim.frameTime;    // Set the total time the animation takes
        tempAnim.currAnimTime = 0.0f;                                        // Set the current time to zero

        MD5Model.animations.push_back(tempAnim);                            // Push back the animation into our model object
    }
    else    // If the file was not loaded
    {
        SwapChain->SetFullscreenState(false, NULL);    // Make sure we are out of fullscreen

        // create message
        std::wstring message = L"Could not open: ";
        message += filename;

        MessageBox(0, message.c_str(),                // display message
            L"Error", MB_OK);

        return false;
    }
    return true;
}

void UpdateMD5Model(Model3D& MD5Model, float deltaTime, int animation)
{
    MD5Model.animations[animation].currAnimTime += deltaTime;            // ���µ�ǰ����ʱ��

    if(MD5Model.animations[animation].currAnimTime > MD5Model.animations[animation].totalAnimTime)
        MD5Model.animations[animation].currAnimTime = 0.0f;

    // ��ǰ����֡
    float currentFrame = MD5Model.animations[animation].currAnimTime * MD5Model.animations[animation].frameRate;    
    int frame0 = floorf( currentFrame );
    int frame1 = frame0 + 1;

    // ȷ�����ᳬ��֡������
    if(frame0 == MD5Model.animations[animation].numFrames-1)
        frame1 = 0;

    float interpolation = currentFrame - frame0;    // ��ȡframe0��frame1֮���������Ϊ��ֵ����

    std::vector<Joint> interpolatedSkeleton;        // ����һ��֡�������洢��ֵ�Ĺ���

    // �����ֵ����
    for( int i = 0; i < MD5Model.animations[animation].numJoints; i++)
    {
        Joint tempJoint;
        Joint joint0 = MD5Model.animations[animation].frameSkeleton[frame0][i];        // ��ȡframe0�Ĺ����ĵ�i���ؽ�
        Joint joint1 = MD5Model.animations[animation].frameSkeleton[frame1][i];        // ��ȡframe1�Ĺ����ĵ�i���ؽ�

        tempJoint.parentID = joint0.parentID;                                            // ����tempJoint�ĸ��ڵ�id

        // ��������Ԫ��ת����XMVECTOR
        XMVECTOR joint0Orient = XMVectorSet(joint0.orientation.x, joint0.orientation.y, joint0.orientation.z, joint0.orientation.w);
        XMVECTOR joint1Orient = XMVectorSet(joint1.orientation.x, joint1.orientation.y, joint1.orientation.z, joint1.orientation.w);

        // ��ֵλ��
        tempJoint.pos.x = joint0.pos.x + (interpolation * (joint1.pos.x - joint0.pos.x));
        tempJoint.pos.y = joint0.pos.y + (interpolation * (joint1.pos.y - joint0.pos.y));
        tempJoint.pos.z = joint0.pos.z + (interpolation * (joint1.pos.z - joint0.pos.z));

        // ʹ���������Բ�ֵ(Slerp)��ֵ����
        XMStoreFloat4(&tempJoint.orientation, XMQuaternionSlerp(joint0Orient, joint1Orient, interpolation));

        interpolatedSkeleton.push_back(tempJoint);        // ���ؽ�push����ֵ�Ĺ���
    }

    for ( int k = 0; k < MD5Model.numSubsets; k++)
    {
        for ( int i = 0; i < MD5Model.subsets[k].vertices.size(); ++i )
        {
            Vertex tempVert = MD5Model.subsets[k].vertices[i];
            tempVert.pos = XMFLOAT3(0, 0, 0);    // ����ȷ�������λ�ñ����
            tempVert.normal = XMFLOAT3(0,0,0);    // ������㷨��

            // �ܽ�ؽں�Ȩ����Ϣ�Ի�ö����λ�úͷ���
            for ( int j = 0; j < tempVert.WeightCount; ++j )
            {
                Weight tempWeight = MD5Model.subsets[k].weights[tempVert.StartWeight + j];
                Joint tempJoint = interpolatedSkeleton[tempWeight.jointID];

                // ���ؽڷ����Ȩ��λ��ת��������
                XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
                XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);

                // �Թؽڷ�����Ԫ����
                XMVECTOR tempJointOrientationConjugate = XMQuaternionInverse(tempJointOrientation);

                // ʹ�ùؽڷ�����Ԫ����������Ԫ�صķ���Ϊ��Ȩ�ؼ��㶥��λ��(�ڹؽڿռ䣬���磬����ԭ����ת)
                // ��ʹ�÷���rotatedPoint = quaternion * point * quaternionConjugate����תһ����
                XMFLOAT3 rotatedPoint;
                XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));

                //������λ�ôӹؽڿռ䣨0,0,0��λ���ƶ�������ռ�Ĺؽ�λ��,Ҫ����Ȩ��ƫ��
                tempVert.pos.x += ( tempJoint.pos.x + rotatedPoint.x ) * tempWeight.bias;
                tempVert.pos.y += ( tempJoint.pos.y + rotatedPoint.y ) * tempWeight.bias;
                tempVert.pos.z += ( tempJoint.pos.z + rotatedPoint.z ) * tempWeight.bias;

                // ����ǰ���Ȩ�ط���Ϊ��֡�������㷨��
                // ��ʹ�ü��㶥��λ��һ���ķ��������㷨�ߣ�ֻ�ǲ���ת������(������ת����)
                XMVECTOR tempWeightNormal = XMVectorSet(tempWeight.normal.x, tempWeight.normal.y, tempWeight.normal.z, 0.0f);

                // ��ת����
                XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightNormal), tempJointOrientationConjugate));

                // ���ӵ����㷨�߲�����Ȩ��ƫ��
                tempVert.normal.x -= rotatedPoint.x * tempWeight.bias;
                tempVert.normal.y -= rotatedPoint.y * tempWeight.bias;
                tempVert.normal.z -= rotatedPoint.z * tempWeight.bias;
            }

            MD5Model.subsets[k].positions[i] = tempVert.pos;                // ������λ�ô洢��λ������������ֱ�Ӵ洢����������
            MD5Model.subsets[k].vertices[i].normal = tempVert.normal;        // �洢���㷨��
            XMStoreFloat3(&MD5Model.subsets[k].vertices[i].normal, XMVector3Normalize(XMLoadFloat3(&MD5Model.subsets[k].vertices[i].normal)));
        }

        // ��λ�÷�����Ӽ��Ķ�����ȥ
        for(int i = 0; i < MD5Model.subsets[k].vertices.size(); i++)
        {
            MD5Model.subsets[k].vertices[i].pos = MD5Model.subsets[k].positions[i];
        }

        // �����Ӽ����㻺��
        // ����������
        D3D11_MAPPED_SUBRESOURCE mappedVertBuff;
        hr = d3d11DevCon->Map(MD5Model.subsets[k].vertBuff, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertBuff);

        // �����ݿ��������㻺����ȥ
        memcpy(mappedVertBuff.pData, &MD5Model.subsets[k].vertices[0], (sizeof(Vertex) * MD5Model.subsets[k].vertices.size()));

        d3d11DevCon->Unmap(MD5Model.subsets[k].vertBuff, 0);

        // ��������ʱ����һ�ָ��»���ķ�ʽ.����Ҫ����һ��ÿ֡��һ�εĻ���ʱ��ʹ�ø÷�����
        // ����GPU��ȡ�����(��DEFAULT�����Ļ��������DYNAMIC������
        // ),����CPUд���������ɳ������ֶ�ʹ���ҳ���һ������
        // ��Ҫʹ����������,����봴��һ����D3D11_USAGE_DEFAULT�Ļ��������D3D11_USAGE_DYNAMIC�Ļ���
        //d3d11DevCon->UpdateSubresource( MD5Model.subsets[k].vertBuff, 0, NULL, &MD5Model.subsets[k].vertices[0], 0, 0 );
    }
}
///////////////**************new**************////////////////////
bool LoadMD5Model(std::wstring filename,
    Model3D& MD5Model,
    std::vector<ID3D11ShaderResourceView*>& shaderResourceViewArray,
    std::vector<std::wstring> texFileNameArray)
{
    std::wifstream fileIn (filename.c_str());        // ���ļ�

    std::wstring checkString;                        // ���������ļ����ַ�

    if(fileIn)                                        // ����ļ��Ƿ��
    {
        while(fileIn)                                // ѭ�����ļ���β
        {    
            fileIn >> checkString;                    // ��ȡ�ļ���һ���ַ�

            if(checkString == L"MD5Version")        // ���MD5�汾������Ϊ�汾10
            {
                /*fileIn >> checkString;
                MessageBox(0, checkString.c_str(),    //��ʾ��Ϣ
                L"MD5Version", MB_OK);*/
            }
            else if ( checkString == L"commandline" )
            {
                std::getline(fileIn, checkString);    // ����ʣ�µ���
            }
            else if ( checkString == L"numJoints" )
            {
                fileIn >> MD5Model.numJoints;        // ����ؽ���
            }
            else if ( checkString == L"numMeshes" )
            {
                fileIn >> MD5Model.numSubsets;        // ����Ҫ���õ���Ƥ��
            }
            else if ( checkString == L"joints" )
            {
                Joint tempJoint;

                fileIn >> checkString;                // ���� "{"

                for(int i = 0; i < MD5Model.numJoints; i++)
                {
                    fileIn >> tempJoint.name;        // ����ؽ���
                    // ��ʱ���ֿ��ܰ����ո�.����������������������ȡֱ��
                    // ������"Ϊֹ
                    if(tempJoint.name[tempJoint.name.size()-1] != '"')
                    {
                        wchar_t checkChar;
                        bool jointNameFound = false;
                        while(!jointNameFound)
                        {
                            checkChar = fileIn.get();

                            if(checkChar == '"')
                                jointNameFound = true;        

                            tempJoint.name += checkChar;                                                            
                        }
                    }

                    fileIn >> tempJoint.parentID;    // ���游�ؽ�

                    fileIn >> checkString;            // ���� "("

                    // ����ؽ�λ�ã���ģ������������ϵ�У������y��z�ᣩ
                    fileIn >> tempJoint.pos.x >> tempJoint.pos.z >> tempJoint.pos.y;

                    fileIn >> checkString >> checkString;    // ���� ")" �� "("

                    // ����ؽڵķ�λ
                    fileIn >> tempJoint.orientation.x >> tempJoint.orientation.z >> tempJoint.orientation.y;

                    // ɾ���ؽ�����˫����
                    tempJoint.name.erase(0, 1);
                    tempJoint.name.erase(tempJoint.name.size()-1, 1);

                    // ������Ԫ�ص�w�ᣨMD5ģ��ʹ��3D��������ʾ��ͷ��Եķ��򡣵�����Ҫ����תΪ��Ԫ�أ�ͬʱ
                    // ��Ԫ�ع����ķ�ʽΪxyzֵ��ʾ��ת�ᣬwֵ��ʾ��ת�Ƕȣ�����0��1֮��
                    float t = 1.0f - ( tempJoint.orientation.x * tempJoint.orientation.x )
                        - ( tempJoint.orientation.y * tempJoint.orientation.y )
                        - ( tempJoint.orientation.z * tempJoint.orientation.z );
                    if ( t < 0.0f )
                    {
                        tempJoint.orientation.w = 0.0f;
                    }
                    else
                    {
                        tempJoint.orientation.w = -sqrtf(t);
                    }

                    std::getline(fileIn, checkString);        // ��������ʣ�ಿ��

                    MD5Model.joints.push_back(tempJoint);    // ���ؽڱ����ģ�͵Ĺؽ�������
                }

                fileIn >> checkString;                    // ����"}"
            }
            else if ( checkString == L"mesh")
            {
                ModelSubset subset;
                int numVerts, numTris, numWeights;

                fileIn >> checkString;                    // ����"{"

                fileIn >> checkString;
                while ( checkString != L"}" )            // һֱ��ȡ�� '}' Ϊֹ
                {
                    // ������Ϊ����������������Ѿ�����������.
                    // ����ͨ���������ǲ����� (�����ڲ��ʿ��У��ڼ���.obj�ļ�ʱ��֪�����ʿ��Ǳ�����.mtl�ļ��еģ�
                    if(checkString == L"shader")        // �������������
                    {                        
                        std::wstring fileNamePath;
                        fileIn >> fileNamePath;            // ��ȡ������

                        // ���ļ�������������пո�ʱ��Ҫ����
                        if(fileNamePath[fileNamePath.size()-1] != '"')
                        {
                            wchar_t checkChar;
                            bool fileNameFound = false;
                            while(!fileNameFound)
                            {
                                checkChar = fileIn.get();

                                if(checkChar == '"')
                                    fileNameFound = true;

                                fileNamePath += checkChar;                                                                    
                            }
                        }

                        // ɾ������·��������
                        fileNamePath.erase(0, 1);
                        fileNamePath.erase(fileNamePath.size()-1, 1);

                        //��������Ƿ��Ѿ�����
                        bool alreadyLoaded = false;
                        for(int i = 0; i < texFileNameArray.size(); ++i)
                        {
                            if(fileNamePath == texFileNameArray[i])
                            {
                                alreadyLoaded = true;
                                subset.texArrayIndex = i;
                            }
                        }

                        //������û�м��أ����ڼ���
                        if(!alreadyLoaded)
                        {
                            ID3D11ShaderResourceView* tempMeshSRV;
                            hr = D3DX11CreateShaderResourceViewFromFile( d3d11Device, fileNamePath.c_str(),
                                NULL, NULL, &tempMeshSRV, NULL );
                            if(SUCCEEDED(hr))
                            {
                                texFileNameArray.push_back(fileNamePath.c_str());
                                subset.texArrayIndex = shaderResourceViewArray.size();
                                shaderResourceViewArray.push_back(tempMeshSRV);
                            }
                            else
                            {
                                MessageBox(0, fileNamePath.c_str(),        //��ʾ��Ϣ
                                    L"Could Not Open:", MB_OK);
                                return false;
                            }
                        }    

                        std::getline(fileIn, checkString);                // ��������ʣ�ಿ��
                    }
                    else if ( checkString == L"numverts")
                    {
                        fileIn >> numVerts;                                // ���涥����

                        std::getline(fileIn, checkString);                // ��������ʣ�ಿ��

                        for(int i = 0; i < numVerts; i++)
                        {
                            Vertex tempVert;

                            fileIn >> checkString                        // ���� "vert # ("
                                >> checkString
                                >> checkString;

                            fileIn >> tempVert.texCoord.x                // ����tex����
                                >> tempVert.texCoord.y;    

                            fileIn >> checkString;                        // ���� ")"

                            fileIn >> tempVert.StartWeight;                // ������Ҫ��Ȩ��Ȩ������

                            fileIn >> tempVert.WeightCount;                // �������Ȩ����

                            std::getline(fileIn, checkString);            // ��������ʣ�ಿ��

                            subset.vertices.push_back(tempVert);        // ������push����Ƥ�Ӽ�����������
                        }
                    }
                    else if ( checkString == L"numtris")
                    {
                        fileIn >> numTris;
                        subset.numTriangles = numTris;

                        std::getline(fileIn, checkString);                // ��������ʣ�ಿ��

                        for(int i = 0; i < numTris; i++)                // ��ѯÿ��������
                        {
                            DWORD tempIndex;
                            fileIn >> checkString;                        // ���� "tri"
                            fileIn >> checkString;                        // ���� tri����

                            for(int k = 0; k < 3; k++)                    // ����3������
                            {
                                fileIn >> tempIndex;
                                subset.indices.push_back(tempIndex);
                            }

                            std::getline(fileIn, checkString);            // ��������ʣ�ಿ��
                        }
                    }
                    else if ( checkString == L"numweights")
                    {
                        fileIn >> numWeights;

                        std::getline(fileIn, checkString);                // ��������ʣ�ಿ��

                        for(int i = 0; i < numWeights; i++)
                        {
                            Weight tempWeight;
                            fileIn >> checkString >> checkString;        // ���� "weight #"

                            fileIn >> tempWeight.jointID;                // ���� weight�Ĺؽ�ID

                            fileIn >> tempWeight.bias;                    // ����ʩ���ڶ����ϵ�weight��Ӱ��

                            fileIn >> checkString;                        // ���� "("

                            fileIn >> tempWeight.pos.x                    // ����ؽڵ�ģ�Ϳռ��Ȩ�ص�λ��
                                >> tempWeight.pos.z
                                >> tempWeight.pos.y;

                            std::getline(fileIn, checkString);            // ��������ʣ�ಿ��

                            subset.weights.push_back(tempWeight);        // ����ʱ�ؽ�push����Ƥ�Ӽ�Ȩ��������
                        }

                    }
                    else
                        std::getline(fileIn, checkString);                // ��������ʣ�ಿ��

                    fileIn >> checkString;                                // ���� "}"
                }

                //*** ʹ�ùؽں�Ȩ�صõ�ÿ������λ����Ϣ ***//
                for ( int i = 0; i < subset.vertices.size(); ++i )
                {
                    Vertex tempVert = subset.vertices[i];
                    tempVert.pos = XMFLOAT3(0, 0, 0);    // ȷ������λ�����ȱ����

                    // ���ؽں�Ȩ����Ϣ��ӵõ������λ����Ϣ
                    for ( int j = 0; j < tempVert.WeightCount; ++j )
                    {
                        Weight tempWeight = subset.weights[tempVert.StartWeight + j];
                        Joint tempJoint = MD5Model.joints[tempWeight.jointID];

                        // Ϊ�����׼��㽫�ؽڷ����Ȩ��λ��ת��������
                        // ����3d����ת������Ԫ��ʱ��Ҫ��w��Ϊ0������
                        // ������Ԫ��תΪ3d����ʱ��ֻ��Ҫ����w����
                        XMVECTOR tempJointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
                        XMVECTOR tempWeightPos = XMVectorSet(tempWeight.pos.x, tempWeight.pos.y, tempWeight.pos.z, 0.0f);

                        // ��Ҫʹ�ùؽڷ�λ��Ԫ�صĹ���
                        // ��x,y,z���漴�ɵõ���Ԫ�صĹ���
                        XMVECTOR tempJointOrientationConjugate = XMVectorSet(-tempJoint.orientation.x, -tempJoint.orientation.y, -tempJoint.orientation.z, tempJoint.orientation.w);

                        // ���㶥��λ�ã��ڹؽڿռ䣬���磬��Ը�Ȩ�أ�ͨ���ؽڷ�λ��Ԫ���Լ����Ĺ���������ԭ��(0,0,0)��ת�õ㣩
                        // ͨ������ʽrotatedPoint = quaternion * point * quaternionConjugate�Լ�������Ԫ������ת��
                        XMFLOAT3 rotatedPoint;
                        XMStoreFloat3(&rotatedPoint, XMQuaternionMultiply(XMQuaternionMultiply(tempJointOrientation, tempWeightPos), tempJointOrientationConjugate));

                        // ���ڽ��ؽڿռ�Ķ���λ��ת��������ռ�Ĺؽ�λ�ã�����Ȩ��ƫ��
                        // ����Ȩ��ƫ������Ϊ��Ȩ�ؿ��ܻ�Զ��������λ����Ӱ�졣ÿ��Ȩ�ع�����һ���ؽڡ�
                        tempVert.pos.x += ( tempJoint.pos.x + rotatedPoint.x ) * tempWeight.bias;
                        tempVert.pos.y += ( tempJoint.pos.y + rotatedPoint.y ) * tempWeight.bias;
                        tempVert.pos.z += ( tempJoint.pos.z + rotatedPoint.z ) * tempWeight.bias;

                        // �������˼�ǣ���Ȩ��λ�ú͹ؽ�λ����ϵ����
                        // ���ͨ��ʹ�ñ�ʾ�ؽ���ת����Ԫ������תȨ��λ�ã��Ա�Ȩ���ܹ�������ռ����ţ�0,0,0����ת��
                        // ��rotatedPoint�����б������ת�㣬������ӵ�����ռ�Ĺؽ�λ���ϣ�����������ռ������ţ�0,0,0����תȨ�ص�λ��,
						//����Ҫ��������ת��,�Ա��ܹ��������������Źؽ�λ����ת��
                        // ��󽫽����Ȩ��ƫ������ն���λ����Ȩ��Ӱ��Ĵ�С����ˡ�����Ӱ�쵥������λ�õ�Ȩ��ƫ�����ӵ�1
                        
                    }

                    subset.positions.push_back(tempVert.pos);            // ������λ�ñ����λ������������ֱ�ӱ������������
                    // ���ڿ��ܻ�����Ҫ����ײ��ʰȡ��ʹ�õ�λ������
                    // ������ʹ�õ���������ṹ
                }

                // ��λ�ñ������Ƥ��������
                for(int i = 0; i < subset.vertices.size(); i++)
                {
                    subset.vertices[i].pos = subset.positions[i];
                }

                //*** ʹ�÷���ƽ�������㶥�㷨�� ***///
                std::vector<XMFLOAT3> tempNormal;

                //�淶�Ͳ��淶�ķ���
                XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

                //������vertsλ�û�ȡ����
                float vecX, vecY, vecZ;

                //�����ε�������
                XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
                XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

                //�����淨��
                for(int i = 0; i < subset.numTriangles; ++i)
                {
                    //��ȡ��ʾһ�������εıߵ�����(edge 0,1)
                    vecX = subset.vertices[subset.indices[(i*3)]].pos.x - subset.vertices[subset.indices[(i*3)+2]].pos.x;
                    vecY = subset.vertices[subset.indices[(i*3)]].pos.y - subset.vertices[subset.indices[(i*3)+2]].pos.y;
                    vecZ = subset.vertices[subset.indices[(i*3)]].pos.z - subset.vertices[subset.indices[(i*3)+2]].pos.z;        
                    edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //������һ����

                    //��ȡ��ʾ��һ�������εıߵ�����(edge 2,1)
                    vecX = subset.vertices[subset.indices[(i*3)+2]].pos.x - subset.vertices[subset.indices[(i*3)+1]].pos.x;
                    vecY = subset.vertices[subset.indices[(i*3)+2]].pos.y - subset.vertices[subset.indices[(i*3)+1]].pos.y;
                    vecZ = subset.vertices[subset.indices[(i*3)+2]].pos.z - subset.vertices[subset.indices[(i*3)+1]].pos.z;        
                    edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);    //�����ڶ�����

                    //��������������Ի�ȡ�ǹ淶���淨��
                    XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));

                    tempNormal.push_back(unnormalized);
                }

                //���㶥�㷨�ߣ�����ƽ������
                XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
                int facesUsing = 0;
                float tX, tY, tZ;    //��ʱ�����

                //����ÿ������
                for(int i = 0; i < subset.vertices.size(); ++i)
                {
                    //����ĸ�������ʹ�øö���
                    for(int j = 0; j < subset.numTriangles; ++j)
                    {
                        if(subset.indices[j*3] == i ||
                            subset.indices[(j*3)+1] == i ||
                            subset.indices[(j*3)+2] == i)
                        {
                            tX = XMVectorGetX(normalSum) + tempNormal[j].x;
                            tY = XMVectorGetY(normalSum) + tempNormal[j].y;
                            tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

                            normalSum = XMVectorSet(tX, tY, tZ, 0.0f);    //��һ����ʹ�ö��㣬���ǹ淶���淨�����ӵ�normalSum

                            facesUsing++;
                        }
                    }

                    //ͨ���ù���ͬһ���������������normalSum�õ���ʵ����
                    normalSum = normalSum / facesUsing;

                    //�淶��normalSum����
                    normalSum = XMVector3Normalize(normalSum);

                    //�����ߺ����߱������ǰ����
                    subset.vertices[i].normal.x = -XMVectorGetX(normalSum);
                    subset.vertices[i].normal.y = -XMVectorGetY(normalSum);
                    subset.vertices[i].normal.z = -XMVectorGetZ(normalSum);

 ///////////////**************new**************////////////////////
                    // Ϊ�˸����׼��㷨���ڶ����д����ؽڿռ䷨��
                    Vertex tempVert = subset.vertices[i];                        // ��ȡ��ǰ����
                    subset.jointSpaceNormals.push_back(XMFLOAT3(0,0,0));        // push��һ���հ׷���
                    XMVECTOR normal = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);        // �������

                    for ( int k = 0; k < tempVert.WeightCount; k++)                // ����ÿһ������Ȩ��
                    {
                        Joint tempJoint = MD5Model.joints[subset.weights[tempVert.StartWeight + k].jointID];    // ��ȡ�ؽڷ���
                        XMVECTOR jointOrientation = XMVectorSet(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);

                        // ���ڹؽڷ�����㷨��(ת�����ؽڿռ�)
                        normal = XMQuaternionMultiply(XMQuaternionMultiply(XMQuaternionInverse(jointOrientation), normalSum), jointOrientation);        

                        XMStoreFloat3(&subset.weights[tempVert.StartWeight + k].normal, XMVector3Normalize(normal));            // ���淶��Ԫ�ش洢��Ȩ�ط���
                    }                
                    ///////////////**************new**************////////////////////
                    //Ϊ��һ���������normalSum,faceUsing
                    normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
                    facesUsing = 0;
                }

                // ������������
                D3D11_BUFFER_DESC indexBufferDesc;
                ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

                indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
                indexBufferDesc.ByteWidth = sizeof(DWORD) * subset.numTriangles * 3;
                indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
                indexBufferDesc.CPUAccessFlags = 0;
                indexBufferDesc.MiscFlags = 0;

                D3D11_SUBRESOURCE_DATA iinitData;

                iinitData.pSysMem = &subset.indices[0];
                d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &subset.indexBuff);

                //�������㻺��
                D3D11_BUFFER_DESC vertexBufferDesc;
                ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

                vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;                            // ����������¸û��壬���Ҫ��Ϊ��̬��
                vertexBufferDesc.ByteWidth = sizeof( Vertex ) * subset.vertices.size();
                vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;                // ����cpuд�������Ȩ��
                vertexBufferDesc.MiscFlags = 0;

                D3D11_SUBRESOURCE_DATA vertexBufferData; 

                ZeroMemory( &vertexBufferData, sizeof(vertexBufferData) );
                vertexBufferData.pSysMem = &subset.vertices[0];
                hr = d3d11Device->CreateBuffer( &vertexBufferDesc, &vertexBufferData, &subset.vertBuff);

                // ��ʱ��Ƥpush��ģ�͵���Ƥ������
                MD5Model.subsets.push_back(subset);
            }
        }
    }
    else
    {
        SwapChain->SetFullscreenState(false, NULL);    // ȷ���˳�ȫ��

        // ������Ϣ
        std::wstring message = L"Could not open: ";
        message += filename;

        MessageBox(0, message.c_str(),    // ��ʾ��Ϣ
            L"Error", MB_OK);

        return false;
    }

    return true;
}
///////////////**************new**************////////////////////
bool LoadObjModel(std::wstring filename, 
	ID3D11Buffer** vertBuff, 
	ID3D11Buffer** indexBuff,
	std::vector<int>& subsetIndexStart,
	std::vector<int>& subsetMaterialArray,
	std::vector<SurfaceMaterial>& material, 
	int& subsetCount,
	bool isRHCoordSys,
    bool computeNormals)
{
	HRESULT hr = 0;

	std::wifstream fileIn (filename.c_str());	//���ļ�
	std::wstring meshMatLib;					//����obj���ʿ��ļ������ַ���

	//�洢����ģ�͵���Ϣ������
	std::vector<DWORD> indices;
	std::vector<XMFLOAT3> vertPos;
	std::vector<XMFLOAT3> vertNorm;
	std::vector<XMFLOAT2> vertTexCoord;
	std::vector<std::wstring> meshMaterials;

	//���㶨������
	std::vector<int> vertPosIndex;
	std::vector<int> vertNormIndex;
	std::vector<int> vertTCIndex;

	//���û�ж�������������֣�ȷ����һ��Ĭ�ϵ�ֵ
	bool hasTexCoord = false;
	bool hasNorm = false;

	//���ڴ洢��������ʱ����
	std::wstring meshMaterialsTemp;
	int vertPosIndexTemp;
	int vertNormIndexTemp;
	int vertTCIndexTemp;

	wchar_t checkChar;		//ÿ�δ��ļ�����һ���ַ�Ҫ�洢�ĵط�
	std::wstring face;		//��������涥����ַ���
	int vIndex = 0;			//���ٶ���������
	int triangleCount = 0;	//����������
	int totalVerts = 0;
	int meshTriangles = 0;

	//����ļ��Ƿ񱻴�
	if (fileIn)
	{
		while(fileIn)
		{			
			checkChar = fileIn.get();	//��ȡ��һ���ַ�

			switch (checkChar)
			{		
			case '#':
				checkChar = fileIn.get();
				while(checkChar != '\n')
					checkChar = fileIn.get();
				break;
			case 'v':	//��ȡ����������
				checkChar = fileIn.get();
				if(checkChar == ' ')	//v - ����λ��
				{
					float vz, vy, vx;
					fileIn >> vx >> vy >> vz;	//�洢��������������

					if(isRHCoordSys)	//��ģ��������������ϵ
						vertPos.push_back(XMFLOAT3( vx, vy, vz * -1.0f));	//ת��Z��
					else
						vertPos.push_back(XMFLOAT3( vx, vy, vz));
				}
				if(checkChar == 't')	//vt - ������������
				{			
					float vtcu, vtcv;
					fileIn >> vtcu >> vtcv;		//�������������������

					if(isRHCoordSys)	//��ģ��������������ϵ
						vertTexCoord.push_back(XMFLOAT2(vtcu, 1.0f-vtcv));	//��v�ᷭת
					else
						vertTexCoord.push_back(XMFLOAT2(vtcu, vtcv));	

					hasTexCoord = true;	//ģ��ʹ����������ϵ
				}
				//���������ں������㷨�ߣ����ǲ����ڴ˼�ⷨ��
				//In the file, but i'll do it here anyway
				if(checkChar == 'n')	//vn - ���㷨��
				{
					float vnx, vny, vnz;
					fileIn >> vnx >> vny >> vnz;	//�洢��������������

					if(isRHCoordSys)	//��ģ��������������ϵ
						vertNorm.push_back(XMFLOAT3( vnx, vny, vnz * -1.0f ));	//��z�ᷭת
					else
						vertNorm.push_back(XMFLOAT3( vnx, vny, vnz ));	

					hasNorm = true;	//ģ�Ͷ��巨��
				}
				break;

				//���飨�Ӽ���
			case 'g':	//g - ����һ����
				checkChar = fileIn.get();
				if(checkChar == ' ')
				{
					subsetIndexStart.push_back(vIndex);		//�Ӽ���ʼ����
					subsetCount++;
				}
				break;

				//��ȡ������
			case 'f':	//f - ������
				checkChar = fileIn.get();
				if(checkChar == ' ')
				{
					face = L"";
					std::wstring VertDef;	//һ��ʱ�̴洢һ�����㶨��
					triangleCount = 0;

					checkChar = fileIn.get();
					while(checkChar != '\n')
					{
						face += checkChar;			//���ַ����ӵ����ַ���
						checkChar = fileIn.get();	//��ȡ��һ���ַ�
						if(checkChar == ' ')		//��Ϊ�ո�
							triangleCount++;		//���������μ���
					}

					//�����ַ�����β���ո�
					if(face[face.length()-1] == ' ')
						triangleCount--;	//ÿ���ո����ӵ������μ���

					triangleCount -= 1;		//Ever vertex in the face AFTER the first two are new faces

					std::wstringstream ss(face);

					if(face.length() > 0)
					{
						int firstVIndex, lastVIndex;	//Holds the first and last vertice's index

						for(int i = 0; i < 3; ++i)		//First three vertices (first triangle)
						{
							ss >> VertDef;	//Get vertex definition (vPos/vTexCoord/vNorm)

							std::wstring vertPart;
							int whichPart = 0;		//(vPos, vTexCoord, or vNorm)

							//Parse this string
							for(int j = 0; j < VertDef.length(); ++j)
							{
								if(VertDef[j] != '/')	//If there is no divider "/", add a char to our vertPart
									vertPart += VertDef[j];

								//If the current char is a divider "/", or its the last character in the string
								if(VertDef[j] == '/' || j ==  VertDef.length()-1)
								{
									std::wistringstream wstringToInt(vertPart);	//Used to convert wstring to int

									if(whichPart == 0)	//If vPos
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;		//subtract one since c++ arrays start with 0, and obj start with 1

										//Check to see if the vert pos was the only thing specified
										if(j == VertDef.length()-1)
										{
											vertNormIndexTemp = 0;
											vertTCIndexTemp = 0;
										}
									}

									else if(whichPart == 1)	//If vTexCoord
									{
										if(vertPart != L"")	//Check to see if there even is a tex coord
										{
											wstringToInt >> vertTCIndexTemp;
											vertTCIndexTemp -= 1;	//subtract one since c++ arrays start with 0, and obj start with 1
										}
										else	//If there is no tex coord, make a default
											vertTCIndexTemp = 0;

										//If the cur. char is the second to last in the string, then
										//there must be no normal, so set a default normal
										if(j == VertDef.length()-1)
											vertNormIndexTemp = 0;

									}								
									else if(whichPart == 2)	//If vNorm
									{
										std::wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;		//subtract one since c++ arrays start with 0, and obj start with 1
									}

									vertPart = L"";	//Get ready for next vertex part
									whichPart++;	//Move on to next vertex part					
								}
							}

							//Check to make sure there is at least one subset
							if(subsetCount == 0)
							{
								subsetIndexStart.push_back(vIndex);		//Start index for this subset
								subsetCount++;
							}

							//Avoid duplicate vertices
							bool vertAlreadyExists = false;
							if(totalVerts >= 3)	//Make sure we at least have one triangle to check
							{
								//Loop through all the vertices
								for(int iCheck = 0; iCheck < totalVerts; ++iCheck)
								{
									//If the vertex position and texture coordinate in memory are the same
									//As the vertex position and texture coordinate we just now got out
									//of the obj file, we will set this faces vertex index to the vertex's
									//index value in memory. This makes sure we don't create duplicate vertices
									if(vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
									{
										if(vertTCIndexTemp == vertTCIndex[iCheck])
										{
											indices.push_back(iCheck);		//Set index for this vertex
											vertAlreadyExists = true;		//If we've made it here, the vertex already exists
										}
									}
								}
							}

							//If this vertex is not already in our vertex arrays, put it there
							if(!vertAlreadyExists)
							{
								vertPosIndex.push_back(vertPosIndexTemp);
								vertTCIndex.push_back(vertTCIndexTemp);
								vertNormIndex.push_back(vertNormIndexTemp);
								totalVerts++;	//We created a new vertex
								indices.push_back(totalVerts-1);	//Set index for this vertex
							}							

							//If this is the very first vertex in the face, we need to
							//make sure the rest of the triangles use this vertex
							if(i == 0)
							{
								firstVIndex = indices[vIndex];	//The first vertex index of this FACE

							}

							//If this was the last vertex in the first triangle, we will make sure
							//the next triangle uses this one (eg. tri1(1,2,3) tri2(1,3,4) tri3(1,4,5))
							if(i == 2)
							{								
								lastVIndex = indices[vIndex];	//The last vertex index of this TRIANGLE
							}
							vIndex++;	//Increment index count
						}

						meshTriangles++;	//One triangle down

						//If there are more than three vertices in the face definition, we need to make sure
						//we convert the face to triangles. We created our first triangle above, now we will
						//create a new triangle for every new vertex in the face, using the very first vertex
						//of the face, and the last vertex from the triangle before the current triangle
						for(int l = 0; l < triangleCount-1; ++l)	//Loop through the next vertices to create new triangles
						{
							//First vertex of this triangle (the very first vertex of the face too)
							indices.push_back(firstVIndex);			//Set index for this vertex
							vIndex++;

							//Second Vertex of this triangle (the last vertex used in the tri before this one)
							indices.push_back(lastVIndex);			//Set index for this vertex
							vIndex++;

							//Get the third vertex for this triangle
							ss >> VertDef;

							std::wstring vertPart;
							int whichPart = 0;

							//Parse this string (same as above)
							for(int j = 0; j < VertDef.length(); ++j)
							{
								if(VertDef[j] != '/')
									vertPart += VertDef[j];
								if(VertDef[j] == '/' || j ==  VertDef.length()-1)
								{
									std::wistringstream wstringToInt(vertPart);

									if(whichPart == 0)
									{
										wstringToInt >> vertPosIndexTemp;
										vertPosIndexTemp -= 1;

										//Check to see if the vert pos was the only thing specified
										if(j == VertDef.length()-1)
										{
											vertTCIndexTemp = 0;
											vertNormIndexTemp = 0;
										}
									}
									else if(whichPart == 1)
									{
										if(vertPart != L"")
										{
											wstringToInt >> vertTCIndexTemp;
											vertTCIndexTemp -= 1;
										}
										else
											vertTCIndexTemp = 0;
										if(j == VertDef.length()-1)
											vertNormIndexTemp = 0;

									}								
									else if(whichPart == 2)
									{
										std::wistringstream wstringToInt(vertPart);

										wstringToInt >> vertNormIndexTemp;
										vertNormIndexTemp -= 1;
									}

									vertPart = L"";
									whichPart++;							
								}
							}					

							//Check for duplicate vertices
							bool vertAlreadyExists = false;
							if(totalVerts >= 3)	//Make sure we at least have one triangle to check
							{
								for(int iCheck = 0; iCheck < totalVerts; ++iCheck)
								{
									if(vertPosIndexTemp == vertPosIndex[iCheck] && !vertAlreadyExists)
									{
										if(vertTCIndexTemp == vertTCIndex[iCheck])
										{
											indices.push_back(iCheck);			//Set index for this vertex
											vertAlreadyExists = true;		//If we've made it here, the vertex already exists
										}
									}
								}
							}

							if(!vertAlreadyExists)
							{
								vertPosIndex.push_back(vertPosIndexTemp);
								vertTCIndex.push_back(vertTCIndexTemp);
								vertNormIndex.push_back(vertNormIndexTemp);
								totalVerts++;					//New vertex created, add to total verts
								indices.push_back(totalVerts-1);		//Set index for this vertex
							}

							//Set the second vertex for the next triangle to the last vertex we got		
							lastVIndex = indices[vIndex];	//The last vertex index of this TRIANGLE

							meshTriangles++;	//New triangle defined
							vIndex++;		
						}
					}
				}
				break;

			case 'm':	//mtllib - material library filename
				checkChar = fileIn.get();
				if(checkChar == 't')
				{
					checkChar = fileIn.get();
					if(checkChar == 'l')
					{
						checkChar = fileIn.get();
						if(checkChar == 'l')
						{
							checkChar = fileIn.get();
							if(checkChar == 'i')
							{
								checkChar = fileIn.get();
								if(checkChar == 'b')
								{
									checkChar = fileIn.get();
									if(checkChar == ' ')
									{
										//Store the material libraries file name
										fileIn >> meshMatLib;
									}
								}
							}
						}
					}
				}

				break;

			case 'u':	//usemtl - which material to use
				checkChar = fileIn.get();
				if(checkChar == 's')
				{
					checkChar = fileIn.get();
					if(checkChar == 'e')
					{
						checkChar = fileIn.get();
						if(checkChar == 'm')
						{
							checkChar = fileIn.get();
							if(checkChar == 't')
							{
								checkChar = fileIn.get();
								if(checkChar == 'l')
								{
									checkChar = fileIn.get();
									if(checkChar == ' ')
									{
										meshMaterialsTemp = L"";	//Make sure this is cleared

										fileIn >> meshMaterialsTemp; //Get next type (string)

										meshMaterials.push_back(meshMaterialsTemp);
									}
								}
							}
						}
					}
				}
				break;

			default:				
				break;
			}
		}
	}
	else	//If we could not open the file
	{
		SwapChain->SetFullscreenState(false, NULL);	//Make sure we are out of fullscreen

		//create message
		std::wstring message = L"Could not open: ";
		message += filename;

		MessageBox(0, message.c_str(),	//display message
			L"Error", MB_OK);

		return false;
	}

	subsetIndexStart.push_back(vIndex); //There won't be another index start after our last subset, so set it here

	//sometimes "g" is defined at the very top of the file, then again before the first group of faces.
	//This makes sure the first subset does not conatain "0" indices.
	if(subsetIndexStart[1] == 0)
	{
		subsetIndexStart.erase(subsetIndexStart.begin()+1);
		meshSubsets--;
	}

	//Make sure we have a default for the tex coord and normal
	//if one or both are not specified
	if(!hasNorm)
		vertNorm.push_back(XMFLOAT3(0.0f, 0.0f, 0.0f));
	if(!hasTexCoord)
		vertTexCoord.push_back(XMFLOAT2(0.0f, 0.0f));

	//Close the obj file, and open the mtl file
	fileIn.close();
	fileIn.open(meshMatLib.c_str());

	std::wstring lastStringRead;
	int matCount = material.size();	//total materials

	//kdset - ��û��������������ɫ����ʹ�û�������ɫ(ͨ����һ����)
	//If the diffuse color WAS set, then we don't need to set our diffuse color to ambient
	bool kdset = false;

	if (fileIn)
	{
		while(fileIn)
		{
			checkChar = fileIn.get();	//Get next char

			switch (checkChar)
			{
            	//Check for comment
			case '#':
				checkChar = fileIn.get();
				while(checkChar != '\n')
					checkChar = fileIn.get();
				break;

				//Set diffuse color
			case 'K':
				checkChar = fileIn.get();
				if(checkChar == 'd')	//Diffuse Color
				{
					checkChar = fileIn.get();	//remove space

					fileIn >> material[matCount-1].difColor.x;
					fileIn >> material[matCount-1].difColor.y;
					fileIn >> material[matCount-1].difColor.z;

					kdset = true;
				}

				//Ambient Color (We'll store it in diffuse if there isn't a diffuse already)
				if(checkChar == 'a')	
				{					
					checkChar = fileIn.get();	//remove space
					if(!kdset)
					{
						fileIn >> material[matCount-1].difColor.x;
						fileIn >> material[matCount-1].difColor.y;
						fileIn >> material[matCount-1].difColor.z;
					}
				}
				break;

				//Check for transparency
			case 'T':
				checkChar = fileIn.get();
				if(checkChar == 'r')
				{
					checkChar = fileIn.get();	//remove space
					float Transparency;
					fileIn >> Transparency;

					material[matCount-1].difColor.w = Transparency;

					if(Transparency > 0.0f)
						material[matCount-1].transparent = true;
				}
				break;

				//Some obj files specify d for transparency
			case 'd':
				checkChar = fileIn.get();
				if(checkChar == ' ')
				{
					float Transparency;
					fileIn >> Transparency;

					//'d' - 0 being most transparent, and 1 being opaque, opposite of Tr
					Transparency = 1.0f - Transparency;

					material[matCount-1].difColor.w = Transparency;

					if(Transparency > 0.0f)
						material[matCount-1].transparent = true;					
				}
				break;

				//Get the diffuse map (texture)
			case 'm':
				checkChar = fileIn.get();
				if(checkChar == 'a')
				{
					checkChar = fileIn.get();
					if(checkChar == 'p')
					{
						checkChar = fileIn.get();
						if(checkChar == '_')
						{
							//map_Kd - Diffuse map
							checkChar = fileIn.get();
							if(checkChar == 'K')
							{
								checkChar = fileIn.get();
								if(checkChar == 'd')
								{
									std::wstring fileNamePath;

									fileIn.get();	//Remove whitespace between map_Kd and file

									//Get the file path - We read the pathname char by char since
									//pathnames can sometimes contain spaces, so we will read until
									//we find the file extension
									bool texFilePathEnd = false;
									while(!texFilePathEnd)
									{
										checkChar = fileIn.get();

										fileNamePath += checkChar;

										if(checkChar == '.')
										{
											for(int i = 0; i < 3; ++i)
												fileNamePath += fileIn.get();

											texFilePathEnd = true;
										}							
									}

									//check if this texture has already been loaded
									bool alreadyLoaded = false;
									for(int i = 0; i < textureNameArray.size(); ++i)
									{
										if(fileNamePath == textureNameArray[i])
										{
											alreadyLoaded = true;
											material[matCount-1].texArrayIndex = i;
											material[matCount-1].hasTexture = true;
										}
									}

									//if the texture is not already loaded, load it now
									if(!alreadyLoaded)
									{
										ID3D11ShaderResourceView* tempMeshSRV;
										hr = D3DX11CreateShaderResourceViewFromFile( d3d11Device, fileNamePath.c_str(),
											NULL, NULL, &tempMeshSRV, NULL );
										if(SUCCEEDED(hr))
										{
											textureNameArray.push_back(fileNamePath.c_str());
											material[matCount-1].texArrayIndex = meshSRV.size();
											meshSRV.push_back(tempMeshSRV);
											material[matCount-1].hasTexture = true;
										}
									}	
								}
							}
							//map_d - alpha map
							else if(checkChar == 'd')
							{
								//Alpha maps are usually the same as the diffuse map
								//So we will assume that for now by only enabling
								//transparency for this material, as we will already
								//be using the alpha channel in the diffuse map
								material[matCount-1].transparent = true;
							}
							///////////////**************new**************////////////////////
							//map_bump - bump map (we're usinga normal map though)
							else if(checkChar == 'b')
							{
								checkChar = fileIn.get();
								if(checkChar == 'u')
								{
									checkChar = fileIn.get();
									if(checkChar == 'm')
									{
										checkChar = fileIn.get();
										if(checkChar == 'p')
										{
											std::wstring fileNamePath;

											fileIn.get();	//Remove whitespace between map_bump and file

											//Get the file path - We read the pathname char by char since
											//pathnames can sometimes contain spaces, so we will read until
											//we find the file extension
											bool texFilePathEnd = false;
											while(!texFilePathEnd)
											{
												checkChar = fileIn.get();

												fileNamePath += checkChar;

												if(checkChar == '.')
												{
													for(int i = 0; i < 3; ++i)
														fileNamePath += fileIn.get();

													texFilePathEnd = true;
												}							
											}

											//check if this texture has already been loaded
											bool alreadyLoaded = false;
											for(int i = 0; i < textureNameArray.size(); ++i)
											{
												if(fileNamePath == textureNameArray[i])
												{
													alreadyLoaded = true;
													material[matCount-1].normMapTexArrayIndex = i;
													material[matCount-1].hasNormMap = true;
												}
											}

											//if the texture is not already loaded, load it now
											if(!alreadyLoaded)
											{
												ID3D11ShaderResourceView* tempMeshSRV;
												hr = D3DX11CreateShaderResourceViewFromFile( d3d11Device, fileNamePath.c_str(),
													NULL, NULL, &tempMeshSRV, NULL );
												if(SUCCEEDED(hr))
												{
													textureNameArray.push_back(fileNamePath.c_str());
													material[matCount-1].normMapTexArrayIndex = meshSRV.size();
													meshSRV.push_back(tempMeshSRV);
													material[matCount-1].hasNormMap = true;
												}
											}	
										}
									}
								}
							}
							///////////////**************new**************////////////////////
						}
					}
				}
				break;

			case 'n':	//newmtl - Declare new material
				checkChar = fileIn.get();
				if(checkChar == 'e')
				{
					checkChar = fileIn.get();
					if(checkChar == 'w')
					{
						checkChar = fileIn.get();
						if(checkChar == 'm')
						{
							checkChar = fileIn.get();
							if(checkChar == 't')
							{
								checkChar = fileIn.get();
								if(checkChar == 'l')
								{
									checkChar = fileIn.get();
									if(checkChar == ' ')
									{
										//New material, set its defaults
										SurfaceMaterial tempMat;
										material.push_back(tempMat);
										fileIn >> material[matCount].matName;
										material[matCount].transparent = false;
										material[matCount].hasTexture = false;
										///////////////**************new**************////////////////////
										material[matCount].hasNormMap = false;
										material[matCount].normMapTexArrayIndex = 0;
										///////////////**************new**************////////////////////
										material[matCount].texArrayIndex = 0;
										matCount++;
										kdset = false;
									}
								}
							}
						}
					}
				}
				break;

			default:
				break;
			}
		}
	}	
	else
	{
		SwapChain->SetFullscreenState(false, NULL);	//Make sure we are out of fullscreen

		std::wstring message = L"Could not open: ";
		message += meshMatLib;

		MessageBox(0, message.c_str(),
			L"Error", MB_OK);

		return false;
	}

	//Set the subsets material to the index value
	//of the its material in our material array
	for(int i = 0; i < meshSubsets; ++i)
	{
		bool hasMat = false;
		for(int j = 0; j < material.size(); ++j)
		{
			if(meshMaterials[i] == material[j].matName)
			{
				subsetMaterialArray.push_back(j);
				hasMat = true;
			}
		}
		if(!hasMat)
			subsetMaterialArray.push_back(0); //Use first material in array
	}

	std::vector<Vertex> vertices;
	Vertex tempVert;

	//Create our vertices using the information we got 
	//from the file and store them in a vector
	for(int j = 0 ; j < totalVerts; ++j)
	{
		tempVert.pos = vertPos[vertPosIndex[j]];
		tempVert.normal = vertNorm[vertNormIndex[j]];
		tempVert.texCoord = vertTexCoord[vertTCIndex[j]];

		vertices.push_back(tempVert);
		///////////////**************new**************////////////////////
	}

    //////////////////////Compute Normals///////////////////////////
    //If computeNormals was set to true then we will create our own
    //normals, if it was set to false we will use the obj files normals
    if(computeNormals)
    {
        std::vector<XMFLOAT3> tempNormal;

		//normalized and unnormalized normals
		XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

		///////////////**************new**************////////////////////
		//tangent stuff
		std::vector<XMFLOAT3> tempTangent;
		XMFLOAT3 tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
		float tcU1, tcV1, tcU2, tcV2;
		///////////////**************new**************////////////////////
		//Used to get vectors (sides) from the position of the verts
		float vecX, vecY, vecZ;

		//Two edges of our triangle
		XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

		//Compute face normals
		for(int i = 0; i < meshTriangles; ++i)
		{
			//Get the vector describing one edge of our triangle (edge 0,2)
			vecX = vertices[indices[(i*3)]].pos.x - vertices[indices[(i*3)+2]].pos.x;
			vecY = vertices[indices[(i*3)]].pos.y - vertices[indices[(i*3)+2]].pos.y;
			vecZ = vertices[indices[(i*3)]].pos.z - vertices[indices[(i*3)+2]].pos.z;		
			edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our first edge

			//Get the vector describing another edge of our triangle (edge 2,1)
			vecX = vertices[indices[(i*3)+2]].pos.x - vertices[indices[(i*3)+1]].pos.x;
			vecY = vertices[indices[(i*3)+2]].pos.y - vertices[indices[(i*3)+1]].pos.y;
			vecZ = vertices[indices[(i*3)+2]].pos.z - vertices[indices[(i*3)+1]].pos.z;		
			edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);	//Create our second edge

			//Cross multiply the two edge vectors to get the un-normalized face normal
			XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));

			tempNormal.push_back(unnormalized);

			///////////////**************new**************////////////////////
			//Find first texture coordinate edge 2d vector
			tcU1 = vertices[indices[(i*3)]].texCoord.x - vertices[indices[(i*3)+2]].texCoord.x;
			tcV1 = vertices[indices[(i*3)]].texCoord.y - vertices[indices[(i*3)+2]].texCoord.y;

			//Find second texture coordinate edge 2d vector
			tcU2 = vertices[indices[(i*3)+2]].texCoord.x - vertices[indices[(i*3)+1]].texCoord.x;
			tcV2 = vertices[indices[(i*3)+2]].texCoord.y - vertices[indices[(i*3)+1]].texCoord.y;

			//Find tangent using both tex coord edges and position edges
			tangent.x = (tcV1 * XMVectorGetX(edge1) - tcV2 * XMVectorGetX(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
			tangent.y = (tcV1 * XMVectorGetY(edge1) - tcV2 * XMVectorGetY(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
			tangent.z = (tcV1 * XMVectorGetZ(edge1) - tcV2 * XMVectorGetZ(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));

			tempTangent.push_back(tangent);
			///////////////**************new**************////////////////////
		}

		//Compute vertex normals (normal Averaging)
		XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		int facesUsing = 0;
		float tX, tY, tZ;	//temp axis variables

		//Go through each vertex
		for(int i = 0; i < totalVerts; ++i)
		{
			//Check which triangles use this vertex
			for(int j = 0; j < meshTriangles; ++j)
			{
				if(indices[j*3] == i ||
					indices[(j*3)+1] == i ||
					indices[(j*3)+2] == i)
				{
					tX = XMVectorGetX(normalSum) + tempNormal[j].x;
					tY = XMVectorGetY(normalSum) + tempNormal[j].y;
					tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

					normalSum = XMVectorSet(tX, tY, tZ, 0.0f);	//If a face is using the vertex, add the unormalized face normal to the normalSum
					///////////////**************new**************////////////////////		
					//We can reuse tX, tY, tZ to sum up tangents
					tX = XMVectorGetX(tangentSum) + tempTangent[j].x;
					tY = XMVectorGetY(tangentSum) + tempTangent[j].y;
					tZ = XMVectorGetZ(tangentSum) + tempTangent[j].z;

					tangentSum = XMVectorSet(tX, tY, tZ, 0.0f); //sum up face tangents using this vertex
					///////////////**************new**************////////////////////
					facesUsing++;
				}
			}

			//Get the actual normal by dividing the normalSum by the number of faces sharing the vertex
			normalSum = normalSum / facesUsing;
			///////////////**************new**************////////////////////
			tangentSum = tangentSum / facesUsing;
			///////////////**************new**************////////////////////

			//Normalize the normalSum vector
			normalSum = XMVector3Normalize(normalSum);
			///////////////**************new**************////////////////////
			tangentSum =  XMVector3Normalize(tangentSum);
			///////////////**************new**************////////////////////

			//Store the normal in our current vertex
			vertices[i].normal.x = XMVectorGetX(normalSum);
			vertices[i].normal.y = XMVectorGetY(normalSum);
			vertices[i].normal.z = XMVectorGetZ(normalSum);

			///////////////**************new**************////////////////////
			vertices[i].tangent.x = XMVectorGetX(tangentSum);
			vertices[i].tangent.y = XMVectorGetY(tangentSum);
			vertices[i].tangent.z = XMVectorGetZ(tangentSum);
			///////////////**************new**************////////////////////
			//Clear normalSum and facesUsing for next vertex
			normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			///////////////**************new**************////////////////////
			tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
			///////////////**************new**************////////////////////
			facesUsing = 0;

		}
	}

	//Create index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * meshTriangles*3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, indexBuff);

	//Create Vertex Buffer
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof( Vertex ) * totalVerts;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData; 

	ZeroMemory( &vertexBufferData, sizeof(vertexBufferData) );
	vertexBufferData.pSysMem = &vertices[0];
	hr = d3d11Device->CreateBuffer( &vertexBufferDesc, &vertexBufferData, vertBuff);

	return true;
}
///////////////**************new**************////////////////////

void CreateSphere(int LatLines, int LongLines)
{
	NumSphereVertices = ((LatLines-2) * LongLines) + 2;
	NumSphereFaces  = ((LatLines-3)*(LongLines)*2) + (LongLines*2);

	float sphereYaw = 0.0f;
	float spherePitch = 0.0f;

	std::vector<Vertex> vertices(NumSphereVertices);

	XMVECTOR currVertPos = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	vertices[0].pos.x = 0.0f;
	vertices[0].pos.y = 0.0f;
	vertices[0].pos.z = 1.0f;

	for(DWORD i = 0; i < LatLines-2; ++i)
	{
		spherePitch = (i+1) * (3.14f/(LatLines-1));
		Rotationx = XMMatrixRotationX(spherePitch);
		for(DWORD j = 0; j < LongLines; ++j)
		{
			sphereYaw = j * (6.28f/(LongLines));
			Rotationy = XMMatrixRotationZ(sphereYaw);
			currVertPos = XMVector3TransformNormal( XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), (Rotationx * Rotationy) );	
			currVertPos = XMVector3Normalize( currVertPos );
			vertices[i*LongLines+j+1].pos.x = XMVectorGetX(currVertPos);
			vertices[i*LongLines+j+1].pos.y = XMVectorGetY(currVertPos);
			vertices[i*LongLines+j+1].pos.z = XMVectorGetZ(currVertPos);
		}
	}

	vertices[NumSphereVertices-1].pos.x =  0.0f;
	vertices[NumSphereVertices-1].pos.y =  0.0f;
	vertices[NumSphereVertices-1].pos.z = -1.0f;


	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory( &vertexBufferDesc, sizeof(vertexBufferDesc) );

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof( Vertex ) * NumSphereVertices;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData; 

	ZeroMemory( &vertexBufferData, sizeof(vertexBufferData) );
	vertexBufferData.pSysMem = &vertices[0];
	hr = d3d11Device->CreateBuffer( &vertexBufferDesc, &vertexBufferData, &sphereVertBuffer);


	std::vector<DWORD> indices(NumSphereFaces * 3);

	int k = 0;
	for(DWORD l = 0; l < LongLines-1; ++l)
	{
		indices[k] = 0;
		indices[k+1] = l+1;
		indices[k+2] = l+2;
		k += 3;
	}

	indices[k] = 0;
	indices[k+1] = LongLines;
	indices[k+2] = 1;
	k += 3;

	for(DWORD i = 0; i < LatLines-3; ++i)
	{
		for(DWORD j = 0; j < LongLines-1; ++j)
		{
			indices[k]   = i*LongLines+j+1;
			indices[k+1] = i*LongLines+j+2;
			indices[k+2] = (i+1)*LongLines+j+1;

			indices[k+3] = (i+1)*LongLines+j+1;
			indices[k+4] = i*LongLines+j+2;
			indices[k+5] = (i+1)*LongLines+j+2;

			k += 6; // next quad
		}

		indices[k]   = (i*LongLines)+LongLines;
		indices[k+1] = (i*LongLines)+1;
		indices[k+2] = ((i+1)*LongLines)+LongLines;

		indices[k+3] = ((i+1)*LongLines)+LongLines;
		indices[k+4] = (i*LongLines)+1;
		indices[k+5] = ((i+1)*LongLines)+1;

		k += 6;
	}

	for(DWORD l = 0; l < LongLines-1; ++l)
	{
		indices[k] = NumSphereVertices-1;
		indices[k+1] = (NumSphereVertices-1)-(l+1);
		indices[k+2] = (NumSphereVertices-1)-(l+2);
		k += 3;
	}

	indices[k] = NumSphereVertices-1;
	indices[k+1] = (NumSphereVertices-1)-LongLines;
	indices[k+2] = NumSphereVertices-2;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory( &indexBufferDesc, sizeof(indexBufferDesc) );

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * NumSphereFaces * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;

	iinitData.pSysMem = &indices[0];
	d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &sphereIndexBuffer);

}
void InitD2DScreenTexture()
{
	//�������㻺��
	Vertex v[] =
	{
		// Front Face
		Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
		Vertex(-1.0f,  1.0f, -1.0f, 0.0f, 0.0f,-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
		Vertex( 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
		Vertex( 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
	};

	DWORD indices[] = {
		//������
		0, 1, 2,
		0, 2, 3,
	};

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * 2 * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;
	d3d11Device->CreateBuffer(&indexBufferDesc, &iinitData, &d2dIndexBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * 4;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = v;
	hr = d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &d2dVertBuffer);

	//������D2D������һ����ɫ����Դ��ͼ
	//��ˣ��ܹ�ʹ����������һ���������������ڸ��ǳ���
	d3d11Device->CreateShaderResourceView(sharedTex11, NULL, &d2dTexture);

}

//void ReleaseObjects()
//{
//�ͷŴ�����COM����
//	SwapChain->Release();
//	d3d11Device->Release();
//	d3d11DevCon->Release();
//}

bool InitScene()
{
	//
	InitD2DScreenTexture();
	//������ɫ��
	CreateSphere(10, 10);

	///////////////**************new**************////////////////////
    if(!LoadObjModel(L"ground.obj", &meshVertBuff, &meshIndexBuff, meshSubsetIndexStart, meshSubsetTexture, material, meshSubsets, true, true))
        return false;

    ///////////////**************new**************////////////////////
    if(!LoadMD5Model(L"boy.md5mesh", NewMD5Model, meshSRV, textureNameArray))
		return false;
	///////////////**************new**************////////////////////
	    ///////////////**************new**************////////////////////    
    if(!LoadMD5Anim(L"boy.md5anim", NewMD5Model))
        return false;

    // ��ȡ��Χ����Ϣ
   // CreateBoundingVolumes(bottleVertPosArray, bottleBoundingBoxVertPosArray, bottleBoundingBoxVertIndexArray, bottleBoundingSphere, bottleCenterOffset);
	///////////////**************new**************////////////////////
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "VS", "vs_4_0", 0, 0, 0, &VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "PS", "ps_4_0", 0, 0, 0, &PS_Buffer, 0, 0);
	/// new
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "D2D_PS", "ps_4_0", 0, 0, 0, &D2D_PS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_VS", "vs_4_0", 0, 0, 0, &SKYMAP_VS_Buffer, 0, 0);
	hr = D3DX11CompileFromFile(L"Effects.fx", 0, 0, "SKYMAP_PS", "ps_4_0", 0, 0, 0, &SKYMAP_PS_Buffer, 0, 0);

	///////////////**************new**************////////////////////
	//������ɫ������
	hr = d3d11Device->CreateVertexShader(VS_Buffer->GetBufferPointer(), VS_Buffer->GetBufferSize(), NULL, &VS);
	hr = d3d11Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
	///new
	hr = d3d11Device->CreatePixelShader(D2D_PS_Buffer->GetBufferPointer(), D2D_PS_Buffer->GetBufferSize(), NULL, &D2D_PS);
	hr = d3d11Device->CreateVertexShader(SKYMAP_VS_Buffer->GetBufferPointer(), SKYMAP_VS_Buffer->GetBufferSize(), NULL, &SKYMAP_VS);
	hr = d3d11Device->CreatePixelShader(SKYMAP_PS_Buffer->GetBufferPointer(), SKYMAP_PS_Buffer->GetBufferSize(), NULL, &SKYMAP_PS);
	///////////////**************new**************////////////////////
	///////////////**************new**************////////////////////
	//���ö����������ɫ��
	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);

	///////////////**************new**************////////////////////
	light.pos = XMFLOAT3(0.0f, 7.0f, 0.0f);
	light.dir = XMFLOAT3(0.5f, 0.75f, -0.5f);
	light.range = 1000.0f;
	light.cone = 12.0f;
	light.att = XMFLOAT3(0.4f, 0.02f, 0.000f);
	light.ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	light.diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	//Create the Input Layout
	//�������벼��
	d3d11Device->CreateInputLayout(layout, numElements, VS_Buffer->GetBufferPointer(),
		VS_Buffer->GetBufferSize(), &vertLayout);

	//�������벼��
	d3d11DevCon->IASetInputLayout(vertLayout);
	
	//����ͼԪ����
	d3d11DevCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�����ӿ�
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = Width;
	viewport.Height = Height;
	
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	//�����ӿ�
	d3d11DevCon->RSSetViewports(1, &viewport);

	//���������������͵�Ч���ļ���cbuffer
	D3D11_BUFFER_DESC cbbd;
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerObject);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	hr = d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerObjectBuffer);

	//������������ÿ֡����cbuffer����ɫ���ļ�
	ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));
	cbbd.Usage = D3D11_USAGE_DEFAULT;
	cbbd.ByteWidth = sizeof(cbPerFrame);
	cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbbd.CPUAccessFlags = 0;
	cbbd.MiscFlags = 0;

	d3d11Device->CreateBuffer(&cbbd, NULL, &cbPerFrameBuffer);

	//�����Ϣ
	//�����Ϣ
	camPosition = XMVectorSet( 0.0f, 5.0f, -8.0f, 0.0f );
	//camPosition = XMVectorSet(0.0f, 0.0f, -0.5f, 0.0f);
	camTarget = XMVectorSet( 0.0f, 0.5f, 0.0f, 0.0f );
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//������ͼ����
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	//����ͶӰ����
	camProjection = XMMatrixPerspectiveFovLH(0.4f*3.14f, (float)Width / Height, 1.0f, 1000.0f);

	D3D11_BLEND_DESC blendDesc;
    ZeroMemory( &blendDesc, sizeof(blendDesc) );

    D3D11_RENDER_TARGET_BLEND_DESC rtbd;
    ZeroMemory( &rtbd, sizeof(rtbd) );

    rtbd.BlendEnable             = true;
    rtbd.SrcBlend                 = D3D11_BLEND_SRC_COLOR;
    ///////////////**************new**************////////////////////
    rtbd.DestBlend                 = D3D11_BLEND_INV_SRC_ALPHA;
    ///////////////**************new**************////////////////////
    rtbd.BlendOp                 = D3D11_BLEND_OP_ADD;
    rtbd.SrcBlendAlpha             = D3D11_BLEND_ONE;
    rtbd.DestBlendAlpha             = D3D11_BLEND_ZERO;
    rtbd.BlendOpAlpha             = D3D11_BLEND_OP_ADD;
    rtbd.RenderTargetWriteMask     = D3D10_COLOR_WRITE_ENABLE_ALL;

    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = rtbd;
	
	d3d11Device->CreateBlendState(&blendDesc, &d2dTransparency);
	
	///////////////**************new**************////////////////////
	ZeroMemory( &rtbd, sizeof(rtbd) );

	rtbd.BlendEnable			 = true;
	rtbd.SrcBlend				 = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.DestBlend				 = D3D11_BLEND_SRC_ALPHA;
	rtbd.BlendOp				 = D3D11_BLEND_OP_ADD;
	rtbd.SrcBlendAlpha			 = D3D11_BLEND_INV_SRC_ALPHA;
	rtbd.DestBlendAlpha			 = D3D11_BLEND_SRC_ALPHA;
	rtbd.BlendOpAlpha			 = D3D11_BLEND_OP_ADD;
	rtbd.RenderTargetWriteMask	 = D3D10_COLOR_WRITE_ENABLE_ALL;

	blendDesc.AlphaToCoverageEnable = false;
	blendDesc.RenderTarget[0] = rtbd;

	d3d11Device->CreateBlendState(&blendDesc, &Transparency);
	///////////////**************new**************////////////////////
	//����ͼ������
	//hr = 
//#if 1
//	hr = D3DX11CreateShaderResourceViewFromFile(d3d11Device, L"grass.jpg",
//	NULL, NULL, &CubesTexture, NULL);
	///////////////**************new**************////////////////////
	//����D3D�������ڼ���һ������������
	D3DX11_IMAGE_LOAD_INFO loadSMInfo;
	loadSMInfo.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

	//��������
	ID3D11Texture2D* SMTexture = 0;
	hr = D3DX11CreateTextureFromFile(d3d11Device, L"skymap.dds",
		&loadSMInfo, 0, (ID3D11Resource**)&SMTexture, 0);

	//��������������
	D3D11_TEXTURE2D_DESC SMTextureDesc;
	SMTexture->GetDesc(&SMTextureDesc);

	//����D3D������һ������������,����һ��2D����������
	D3D11_SHADER_RESOURCE_VIEW_DESC SMViewDesc;
	SMViewDesc.Format = SMTextureDesc.Format;
	SMViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
	SMViewDesc.TextureCube.MipLevels = SMTextureDesc.MipLevels;
	SMViewDesc.TextureCube.MostDetailedMip = 0;

	//������Դ��ͼ
	hr = d3d11Device->CreateShaderResourceView(SMTexture, &SMViewDesc, &smrv);
	///////////////**************new**************////////////////////

	//���ò���״̬
	D3D11_SAMPLER_DESC sampDesc;
	ZeroMemory(&sampDesc, sizeof(sampDesc));
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	//��������״̬
	hr = d3d11Device->CreateSamplerState(&sampDesc, &CubesTexSamplerState);


	//d3d11Device->CreateBlendState(&blendDesc, &Transparency);

	//������ʱ���˳ʱ��״̬
	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
	cmdesc.FrontCounterClockwise = true;
	hr = d3d11Device->CreateRasterizerState(&cmdesc, &CCWcullMode);

	cmdesc.FrontCounterClockwise = false;
	hr = d3d11Device->CreateRasterizerState(&cmdesc, &CWcullMode);

	///////////////**************new**************////////////////////
	cmdesc.CullMode = D3D11_CULL_NONE;
	hr = d3d11Device->CreateRasterizerState(&cmdesc, &RSCullNone);

	D3D11_DEPTH_STENCIL_DESC dssDesc;
	ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	dssDesc.DepthEnable = true;
	dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

	d3d11Device->CreateDepthStencilState(&dssDesc, &DSLessEqual);

    return true;
}

///////////////**************new**************////////////////////
void StartTimer()
{
    LARGE_INTEGER frequencyCount;
    QueryPerformanceFrequency(&frequencyCount);
    countsPerSecond = double(frequencyCount.QuadPart);

    QueryPerformanceCounter(&frequencyCount);
    CounterStart = frequencyCount.QuadPart;
}

double GetTime()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return double(currentTime.QuadPart-CounterStart)/countsPerSecond;
}

double GetFrameTime()
{
    LARGE_INTEGER currentTime;
    __int64 tickCount;
    QueryPerformanceCounter(&currentTime);

    tickCount = currentTime.QuadPart-frameTimeOld;
    frameTimeOld = currentTime.QuadPart;

    if(tickCount < 0.0f)
        tickCount = 0.0f;

    return float(tickCount)/countsPerSecond;
}
///////////////**************new**************////////////////////

///////////////**************new**************////////////////////
void UpdateScene(double time)
    ///////////////**************new**************////////////////////
//void UpdateScene()
{
	//Reset cube1World
//	groundWorld = XMMatrixIdentity();

	//Define cube1's world space matrix
	///////////////**************new**************////////////////////
//	Scale = XMMatrixScaling( 500.0f, 10.0f, 500.0f );
//	Translation = XMMatrixTranslation( 0.0f, 10.0f, 0.0f );

	//Set cube1's world space using the transformations
//	groundWorld = Scale * Translation;

	//��λ��������
	sphereWorld = XMMatrixIdentity();

	//Define sphereWorld's world space matrix
	Scale = XMMatrixScaling( 5.0f, 5.0f, 5.0f );
	//Make sure the sphere is always centered around camera
	Translation = XMMatrixTranslation( XMVectorGetX(camPosition), XMVectorGetY(camPosition), XMVectorGetZ(camPosition) );

	//Set sphereWorld's world space using the transformations
	sphereWorld = Scale * Translation;

	///////////////**************new**************////////////////////
	meshWorld = XMMatrixIdentity();

	//Define cube1's world space matrix
	Rotation = XMMatrixRotationY(3.14f);
	Scale = XMMatrixScaling( 1.0f, 1.0f, 1.0f );
	Translation = XMMatrixTranslation( 0.0f, 0.0f, 0.0f );

	meshWorld = Rotation * Scale * Translation;
    ///////////////**************new**************////////////////////
    Scale = XMMatrixScaling( 0.04f, 0.04f, 0.04f );            // ��ģ�ͳߴ���С
    Translation = XMMatrixTranslation( 0.0f, 3.0f, 0.0f );
    smilesWorld = Scale * Translation;
    ///////////////**************new**************////////////////////
}

///////////////**************new**************////////////////////
void RenderText(std::wstring text, int inInt)
//void RenderText(std::wstring text)
{
	//�ͷ�D3D11�豸
    d3d11DevCon->PSSetShader(D2D_PS, 0, 0);
	keyedMutex11->ReleaseSync(0);

	//ʹ��D3D10.1�豸
	keyedMutex10->AcquireSync(0, 5);

	//����D2D����
	D2DRenderTarget->BeginDraw();
	//���D2D����ɫ
	D2DRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));


	//�����ַ���
	std::wostringstream printString;
    ///////////////**************new**************////////////////////
    printString << text << inInt;
    printText = printString.str();

	//����������ɫ
    D2D1_COLOR_F FontColor = D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f);

	//����D2D����Ҫ�õ��Ļ�����ɫ
	Brush->SetColor(FontColor);

	//����D2D��Ⱦ����
	D2D1_RECT_F layoutRect = D2D1::RectF(0, 0, Width, Height);

	//�����ı�
	D2DRenderTarget->DrawText(
		printText.c_str(),
		wcslen(printText.c_str()),
        TextFormat,
		layoutRect,
		Brush
		);

	D2DRenderTarget->EndDraw();

	//�ͷ�D3D10.1�豸
	keyedMutex10->ReleaseSync(1);

	//ʹ��D3D11�豸
	keyedMutex11->AcquireSync(1, 5);

	//ʹ����ɫ����Դ��ʾd2d��ȾĿ��������һ�������������þ����Ǳ���Ⱦ����Ļ�ռ�ġ�ʹ�æ�����Ա�����D2D
	//��ȾĿ��ı���Ϊ���ɼ��ģ���ֻ��ʹ��D2D���ƵĶ����ſɼ����ı�����

	//ΪD2D��ȾĿ�������������û��״̬
	d3d11DevCon->OMSetBlendState(d2dTransparency, NULL, 0xffffffff);
   //Set d2d's pixel shader so lighting calculations are not done
  //  d3d11DevCon->PSSetShader(D2D_PS, 0, 0);
	//����d2d��������
 
	d3d11DevCon->IASetIndexBuffer(d2dIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//����d2d���㻺��
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3d11DevCon->IASetVertexBuffers(0, 1, &d2dVertBuffer, &stride, &offset);

	WVP = XMMatrixIdentity();
	///new
//	cbPerObj.World = XMMatrixTranspose(WVP);

	cbPerObj.WVP = XMMatrixTranspose(WVP);
	d3d11DevCon->UpdateSubresource(cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0);
	d3d11DevCon->VSSetConstantBuffers(0, 1, &cbPerObjectBuffer);
	d3d11DevCon->PSSetShaderResources(0, 1, &d2dTexture);
	d3d11DevCon->PSSetSamplers(0, 1, &CubesTexSamplerState);

	d3d11DevCon->RSSetState(CWcullMode);

	//���ڶ���������
	d3d11DevCon->DrawIndexed(6, 0, 0);

}

void DrawScene()
{
	//�����µ���ɫ���󻺳�
//	D3DXCOLOR bgColor(red, green, blue, 1.0f);
//	float bgColor[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
    float bgColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };

	d3d11DevCon->ClearRenderTargetView(renderTargetView, bgColor);

	//ˢ�����ģ����ͼ
	d3d11DevCon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	//new
	constbuffPerFrame.light = light;
	d3d11DevCon->UpdateSubresource(cbPerFrameBuffer, 0, NULL, &constbuffPerFrame, 0, 0);
	d3d11DevCon->PSSetConstantBuffers(0, 1, &cbPerFrameBuffer);
	//��λ�����������ɫ��
//	d3d11DevCon->VSSetShader(VS, 0, 0);
//	d3d11DevCon->PSSetShader(PS, 0, 0);

	//ʹ��Ĭ�Ϲ�դ��״̬
//	d3d11DevCon->RSSetState(NULL);


	//����ʹ�ñ���ü��Ķ���
	//�رձ���ü�
   // d3d11DevCon->RSSetState(noCull);
	d3d11DevCon->OMSetRenderTargets( 1, &renderTargetView, depthStencilView );

	d3d11DevCon->OMSetBlendState(0, 0, 0xffffffff);
	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);

    //Set the cubes index buffer
	//�������������������
//	d3d11DevCon->IASetIndexBuffer(squareIndexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//����������Ķ��㻺��
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
//	d3d11DevCon->IASetVertexBuffers(0, 1, &squareVertBuffer, &stride, &offset);
    ///////////////**************new**************////////////////////
    ///***����MD5ģ��***///
    for(int i = 0; i < NewMD5Model.numSubsets; i ++)
    {
        //���õ�����������
        d3d11DevCon->IASetIndexBuffer( NewMD5Model.subsets[i].indexBuff, DXGI_FORMAT_R32_UINT, 0);
        //���õ��涥�㻺��
        d3d11DevCon->IASetVertexBuffers( 0, 1, &NewMD5Model.subsets[i].vertBuff, &stride, &offset );

        //����WVP���󲢽������뵽Ч���ļ��ĳ�������
        WVP = smilesWorld * camView * camProjection;
        cbPerObj.WVP = XMMatrixTranspose(WVP);    
        cbPerObj.World = XMMatrixTranspose(smilesWorld);    
        cbPerObj.hasTexture = true;        //�������е�md5��Ƥ�Ӽ���������
        cbPerObj.hasNormMap = false;    // ����md5ģ��û�з�����ͼ�������Ҫ�޸�Ҳ������ף�
        d3d11DevCon->UpdateSubresource( cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0 );
        d3d11DevCon->VSSetConstantBuffers( 0, 1, &cbPerObjectBuffer );
        d3d11DevCon->PSSetConstantBuffers( 1, 1, &cbPerObjectBuffer );
        d3d11DevCon->PSSetShaderResources( 0, 1, &meshSRV[NewMD5Model.subsets[i].texArrayIndex] );
        d3d11DevCon->PSSetSamplers( 0, 1, &CubesTexSamplerState );

        d3d11DevCon->RSSetState(RSCullNone);
        d3d11DevCon->DrawIndexed( NewMD5Model.subsets[i].indices.size(), 0, 0 );

    }
    ///////////////**************new**************////////////////////
	//��������ģ�͵ķ�͸���Ӽ�
	for(int i = 0; i < meshSubsets; ++i)
	{
		//���õ�����������
		d3d11DevCon->IASetIndexBuffer( meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
		//���õ��涥�㻺��
		d3d11DevCon->IASetVertexBuffers( 0, 1, &meshVertBuff, &stride, &offset );

		//����WVP���󲢷�������Ч���ļ��еĳ���������
		WVP = meshWorld * camView * camProjection;
		cbPerObj.WVP = XMMatrixTranspose(WVP);	
		cbPerObj.World = XMMatrixTranspose(meshWorld);	
		cbPerObj.difColor = material[meshSubsetTexture[i]].difColor;
		cbPerObj.hasTexture = material[meshSubsetTexture[i]].hasTexture;
		///////////////**************new**************////////////////////
		cbPerObj.hasNormMap = material[meshSubsetTexture[i]].hasNormMap;
		///////////////**************new**************////////////////////
		d3d11DevCon->UpdateSubresource( cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0 );
		d3d11DevCon->VSSetConstantBuffers( 0, 1, &cbPerObjectBuffer );
		d3d11DevCon->PSSetConstantBuffers( 1, 1, &cbPerObjectBuffer );
		if(material[meshSubsetTexture[i]].hasTexture)
			d3d11DevCon->PSSetShaderResources( 0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex] );
		///////////////**************new**************////////////////////
		if(material[meshSubsetTexture[i]].hasNormMap)
			d3d11DevCon->PSSetShaderResources( 1, 1, &meshSRV[material[meshSubsetTexture[i]].normMapTexArrayIndex] );
		///////////////**************new**************////////////////////
		d3d11DevCon->PSSetSamplers( 0, 1, &CubesTexSamplerState );

		d3d11DevCon->RSSetState(RSCullNone);
		int indexStart = meshSubsetIndexStart[i];
		int indexDrawAmount =  meshSubsetIndexStart[i+1] - meshSubsetIndexStart[i];
		if(!material[meshSubsetTexture[i]].transparent)
			d3d11DevCon->DrawIndexed( indexDrawAmount, indexStart, 0 );
	}

    /////Draw the Sky's Sphere//////
    //Set the spheres index buffer
	/////������յ�����//////
	//�����������������
	d3d11DevCon->IASetIndexBuffer( sphereIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//��������Ķ��㻺��
	d3d11DevCon->IASetVertexBuffers( 0, 1, &sphereVertBuffer, &stride, &offset );

	//����WVP���󲢽������͸�Ч���ļ��еĳ�������
	WVP = sphereWorld * camView * camProjection;
	cbPerObj.WVP = XMMatrixTranspose(WVP);	
	cbPerObj.World = XMMatrixTranspose(sphereWorld);	
	d3d11DevCon->UpdateSubresource( cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0 );
	d3d11DevCon->VSSetConstantBuffers( 0, 1, &cbPerObjectBuffer );
	//�������ǵ������ͼ��Դ��ͼ��������ɫ��
	d3d11DevCon->PSSetShaderResources( 0, 1, &smrv );
	d3d11DevCon->PSSetSamplers( 0, 1, &CubesTexSamplerState );

	//�����µ�VS��PS��ɫ��
	d3d11DevCon->VSSetShader(SKYMAP_VS, 0, 0);
	d3d11DevCon->PSSetShader(SKYMAP_PS, 0, 0);
	//�����µ����ģ���RS״̬
	d3d11DevCon->OMSetDepthStencilState(DSLessEqual, 0);
	d3d11DevCon->RSSetState(RSCullNone);
	d3d11DevCon->DrawIndexed( NumSphereFaces * 3, 0, 0 );	

	//����Ĭ�ϵ�VS��PS��ɫ�������ģ��״̬
	d3d11DevCon->VSSetShader(VS, 0, 0);
	d3d11DevCon->PSSetShader(PS, 0, 0);
	d3d11DevCon->OMSetDepthStencilState(NULL, 0);

	///////////////**************new**************////////////////////	
	//�������ǵ�ģ�͵�͸�����Ӽ�
	//�������ǵĻ��״̬
	d3d11DevCon->OMSetBlendState(Transparency, NULL, 0xffffffff);

	for(int i = 0; i < meshSubsets; ++i)
	{
		//���õ�����������
		d3d11DevCon->IASetIndexBuffer( meshIndexBuff, DXGI_FORMAT_R32_UINT, 0);
		//���õ��涥�㻺��
		d3d11DevCon->IASetVertexBuffers( 0, 1, &meshVertBuff, &stride, &offset );

		//����WVP���󲢽������͸�Ч���ļ��еĳ���������
		WVP = meshWorld * camView * camProjection;
		cbPerObj.WVP = XMMatrixTranspose(WVP);	
		cbPerObj.World = XMMatrixTranspose(meshWorld);	
		cbPerObj.difColor = material[meshSubsetTexture[i]].difColor;
		cbPerObj.hasTexture = material[meshSubsetTexture[i]].hasTexture;
		///////////////**************new**************////////////////////
		cbPerObj.hasNormMap = material[meshSubsetTexture[i]].hasNormMap;
		///////////////**************new**************////////////////////
		d3d11DevCon->UpdateSubresource( cbPerObjectBuffer, 0, NULL, &cbPerObj, 0, 0 );
		d3d11DevCon->VSSetConstantBuffers( 0, 1, &cbPerObjectBuffer );
		d3d11DevCon->PSSetConstantBuffers( 1, 1, &cbPerObjectBuffer );
		if(material[meshSubsetTexture[i]].hasTexture)
			d3d11DevCon->PSSetShaderResources( 0, 1, &meshSRV[material[meshSubsetTexture[i]].texArrayIndex] );
		///////////////**************new**************////////////////////
		if(material[meshSubsetTexture[i]].hasNormMap)
			d3d11DevCon->PSSetShaderResources( 1, 1, &meshSRV[material[meshSubsetTexture[i]].normMapTexArrayIndex] );
		///////////////**************new**************////////////////////
		d3d11DevCon->PSSetSamplers( 0, 1, &CubesTexSamplerState );

		d3d11DevCon->RSSetState(RSCullNone);
		int indexStart = meshSubsetIndexStart[i];
		int indexDrawAmount =  meshSubsetIndexStart[i+1] - meshSubsetIndexStart[i];
		if(material[meshSubsetTexture[i]].transparent)
			d3d11DevCon->DrawIndexed( indexDrawAmount, indexStart, 0 );
	}
	///////////////**************new**************////////////////////	
	RenderText(L"FPS: ", fps);

	//Present the backbuffer to the screen
	SwapChain->Present(0, 0);
}

int messageloop(){
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));//����ṹ�屻��ΪNULL��

	while (true)
	{
		//ʹ��PeekMessage()����Ƿ�����Ϣ������
		/*LPMSG lpMsg ��Ϣ�ṹ���ָ��
		*HWND hWnd ������Ϣ�Ĵ��ھ��������ΪNULL����ô����ӵ�ǰ�����н��������κ�һ�����ڵ���Ϣ
		*UINT wMsgFilterMin ָ����Ϣ��Χ�ڵ�һ��Ҫ������Ϣ��ֵ����wMsgFilterMin��wMsgFilterMax����Ϊ0����ôPeekMessage���������е���Ϣ
		*UINT wMsgFilterMax ָ����Ϣ��Χ�����һ��Ҫ������Ϣ��ֵ
		*UINT wRemoveMsg ָ����Ϣ�Ĵ�����ʽ��������ΪPM_REMOVE�����ڶ�ȡ֮��ᱻɾ��
		*/
		BOOL PeekMessageL( 
            LPMSG lpMsg,
            HWND hWnd,
            UINT wMsgFilterMin,
            UINT wMsgFilterMax,
            UINT wRemoveMsg
            );

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
                break;
			//����ϢΪ������Ϣ����������ַ�����TranslateMessage()�����ô�����һЩ���������Ƽ��̵������ֵת�����ַ���ʽ��
			//��DispatchMessage()������Ϣ�����ڹ���WndProc��
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else //��û�д�����Ϣ����������Ϸ
 ///////////////**************new**************////////////////////
		{
  			frameCount++;
 	 		if(GetTime() > 1.0f)
            {
                fps = frameCount;
                frameCount = 0;
                StartTimer();
            }    

            frameTime = GetFrameTime();
		
            ///////////////**************new**************////////////////////
            DetectInput(frameTime);
            ///////////////**************new**************////////////////////
            UpdateScene(frameTime);
			DrawScene();

		}
	}
	return msg.wParam;
}

//������Ϣ��������
//HWND hwnd ��ȡ��Ϣ�Ĵ��ھ��
//UINT msg ��Ϣ������
/*
*WM_ACTIVE �����ڼ���ʱ���͵���Ϣ
*WM_CLOSE �����ڹر�ʱ���͵���Ϣ
*WM_CREATE �����ڴ���ʱ���͵���Ϣ
*WM_DESTROY ����������ʱ���͵���Ϣ
*/
//wParam��lParamʱ��Ϣ�Ķ�����Ϣ��ʹ��wParam��������������Ϣ
LRESULT CALLBACK WndProc(HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	// �����¼������Ϣ�ĵط�����escape�������£�����ʾһ����Ϣ��ѯ���Ƿ�����˳��������yes�������رա��������������Ϣ��رա�����Ϣ����WM_DESTROY
	// ����ζ�Ŵ������ڱ����٣�����0���ҳ���ر�
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(0, L"Are you sure you want to exit?",
				L"Really?", MB_YESNO | MB_ICONASTERISK) == IDYES)
			{
				DestroyWindow(hwnd);
			}
			return 0;

		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
		///////////////**************new**************////////////////////
	//case WM_SIZE:
	//	ClientWidth  = LOWORD(lParam);
	//	ClientHeight = HIWORD(lParam);
	//	return 0;
	//	break;
	default:
		break;
	}

	//����Ĭ�ϴ��ڹ��̺���
	return DefWindowProc(hwnd,
		msg,
		wParam,
		lParam);
}