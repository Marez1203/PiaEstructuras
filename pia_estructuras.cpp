// pia_estructuras.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "pia_estructuras.h"
#include "Resource.h"
#include <fstream>
#include <string.h>
#include <commctrl.h>
#include <commdlg.h>
#include <iostream> 
#include <string> 
#include <ctime>
#include <memory>
#include <windows.h>
#include <ctime>
#include <sstream>
#define MAX_LOADSTRING 100



// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal
SYSTEMTIME* fechactual;
int numeroVueloActual = 0;


struct Pasajero {
    WCHAR tipoVuelo;
    WCHAR usuario;
    WCHAR nombre;
    WCHAR fechaNacimiento;
    WCHAR genero;
    WCHAR nacionalidad;
    int numeroBoleto;
    Pasajero* izquierda;
    Pasajero* derecha;
};

enum EstadoVuelo {
    Pendiente,
    Confirmado,
    Cancelado
};

struct Vuelo {
    WCHAR origen[50];
    WCHAR destino[50];
    WCHAR fechaSalida[MAX_PATH];
    WCHAR fecharegistro[MAX_PATH];
    int vyear;
    int vmonth;
    int vday;
    WCHAR horaregistro[MAX_PATH]; 
    int vhora;
    int vmn;
    int vseg;
    WCHAR numeroVuelo[50];
    WCHAR asientosDisponibles[50];
    WCHAR turistas[50];
    WCHAR ejecutivo[50];
    
    EstadoVuelo estado;
    WCHAR Admus [50];
    WCHAR us[50];
    Vuelo* dato = nullptr;
    Vuelo* siguiente = nullptr;
    Vuelo* anterior = nullptr;
};


struct Usuario {
    WCHAR us [50];
    WCHAR correo[50];
    WCHAR contrasena[50];
    WCHAR nombre[50];
    WCHAR fechaNacimiento[MAX_PATH]; 
    WCHAR genero[50];
    WCHAR foto [MAX_PATH];
    int uyear;
    int umonth;
    int uday;
    Vuelo* vuelos[50];
    WCHAR Admus [50];  
    Usuario* uss;
    Usuario* dato;
    Usuario* siguiente = nullptr;
    Usuario* anterior = nullptr;
};


struct AdmUsuario {
    WCHAR Admus [50];
    WCHAR Admcorreo[50];
    WCHAR Admcontrasena[50];
    WCHAR Admnombre [50];
    WCHAR AdmfechaNacimiento[MAX_PATH];
    WCHAR Admgenero[50];
    WCHAR Admfoto[MAX_PATH];
    int year;
    int month;
    int day;
    SYSTEMTIME fec;
    AdmUsuario* admin;
    Usuario* listaUsuarios; 
    /*AdmUsuario* loggeado;*/
    
    AdmUsuario* siguiente;
    AdmUsuario* anterior;
};

struct NODO_AdmUsuario {
    AdmUsuario* dato;
    NODO_AdmUsuario* loggeado;
    NODO_AdmUsuario* next;
    NODO_AdmUsuario* ante;
};

struct LISTA_ADMUSUARIOS {
    NODO_AdmUsuario* origen;
    NODO_AdmUsuario* fin;
};

NODO_AdmUsuario* loggeado = nullptr;
Usuario* logUsuario = nullptr;
Vuelo* indice = nullptr; 
Vuelo* ci = nullptr;
Usuario* ind = nullptr;
Usuario* cu = nullptr;
//Vuelo* va = nullptr;

struct listaVuelos {
    Vuelo* inicio;
    Vuelo* fin; 
};

class ListaVuelos {
private:

public:
   

    ListaVuelos() : inicio(nullptr), fin(nullptr) {}
    Vuelo* inicio;
    Vuelo* fin;
    
    void agregarVuelo(const WCHAR* origen, const WCHAR* destino, const WCHAR* numeroVuelo, const WCHAR* asientosDisponibles, const WCHAR* turistas, const WCHAR* ejecutivo, const WCHAR* fecharegistro, const WCHAR* horaregistro, int vhora, int vmn, int vseg, const WCHAR* fechaSalida, int vday, int vmonth, int vyear) 
    {
        Vuelo* nuevoVuelo = new Vuelo;
        wcsncpy_s(nuevoVuelo->origen, origen, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->destino, destino, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->numeroVuelo, numeroVuelo, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->asientosDisponibles, asientosDisponibles, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->turistas, turistas, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->ejecutivo, ejecutivo, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->fechaSalida, MAX_PATH, fechaSalida, _TRUNCATE);
        wcsncpy_s(nuevoVuelo->fecharegistro, MAX_PATH, fecharegistro, _TRUNCATE);
        nuevoVuelo->vday = vday;
        nuevoVuelo->vmonth = vmonth;
        nuevoVuelo->vyear = vyear;
        wcsncpy_s(nuevoVuelo->horaregistro, MAX_PATH, horaregistro, _TRUNCATE);
        nuevoVuelo->vhora = vhora;
        nuevoVuelo->vmn = vmn;
        nuevoVuelo->vseg = vseg;

        if (loggeado != nullptr && loggeado->dato != nullptr) {
            wcscpy_s(nuevoVuelo->Admus, 50, loggeado->dato->Admus);
        }
        if (logUsuario != nullptr && logUsuario->dato != nullptr) {
            wcscpy_s(nuevoVuelo->us, 50, logUsuario->dato->us); 
            nuevoVuelo->siguiente = nullptr;
        }

        if (inicio == nullptr) {
            inicio = nuevoVuelo;
            fin = nuevoVuelo;
        }
        else {
            if (fin == nullptr) {
                inicio->siguiente = nuevoVuelo;
                nuevoVuelo->anterior = inicio;
            }
            else {
                nuevoVuelo->anterior = fin;
                fin->siguiente = nuevoVuelo;
            }
        
            fin = nuevoVuelo;
            nuevoVuelo->siguiente = nullptr;
        }
        /*else {
            nuevoVuelo->siguiente = inicio;
            inicio->anterior = nuevoVuelo;
            inicio = nuevoVuelo;

        }*/
        /*else {

            
            nuevoVuelo->anterior = fin;
            fin->siguiente = nuevoVuelo; 
            fin = nuevoVuelo->siguiente = nullptr;
        }*/
    }

    
    int convertToInt(const WCHAR* str) {
        std::wstringstream ss;
        ss << str;
        int num;
        ss >> num;
        return num;
    }

    // Helper function to convert int to WCHAR*
    WCHAR* convertToWCHAR(int num) {
        std::wstringstream ss;
        ss << num;
        std::wstring result = ss.str();
        const WCHAR* converted = result.c_str();
        size_t len = wcslen(converted) + 1;
        WCHAR* buffer = new WCHAR[len];
        wcscpy_s(buffer, len, converted);
        return buffer;
    }

    // Helper function for swapping two nodes
    void swap(Vuelo* v1, Vuelo* v2) {
        Vuelo* temp = v1;
            v1 = v2;
            v2 = temp;
    }

    // Helper function to partition the list and return the pivot element
    Vuelo* partition(Vuelo* low, Vuelo* high) {
        int pivot = convertToInt(high->numeroVuelo);
        Vuelo* i = low->anterior;

        for (Vuelo* j = low; j != high; j = j->siguiente) {
            if (convertToInt(j->numeroVuelo) <= pivot) {
                i = (i == nullptr) ? low : i->siguiente;
                swap(i, j);
            }
        }
        i = (i == nullptr) ? low : i->siguiente;
        swap(i, high);
        return i;
    }

    // Helper function for quicksort
    void quickSortUtil(Vuelo* low, Vuelo* high) {
        if (high != nullptr && low != high && low != high->siguiente) {
            Vuelo* pivot = partition(low, high);
            quickSortUtil(low, pivot->anterior);
            quickSortUtil(pivot->siguiente, high);
        }
    }


    // Your existing code...

    // Method to sort the list by numeroVuelo in ascending order using Quicksort
    void sortList() {
        // Sort using Quicksort
        quickSortUtil(inicio, fin);
    }


};

class ListaUsuarios {
private:

public:

    Usuario* inicio;
    Usuario* fin;

    ListaUsuarios() : inicio(nullptr), fin(nullptr) {}
    void agregarUsuario(const WCHAR* us, const WCHAR* correo, const WCHAR* contrasena, const WCHAR* nombre, const WCHAR* fechaNacimiento, const WCHAR* genero, const WCHAR* foto, int uyear, int uday, int umonth) {
        Usuario* nuevoUsuario = new Usuario;
        wcsncpy_s(nuevoUsuario->us, us, _TRUNCATE);
        wcsncpy_s(nuevoUsuario->correo, correo, _TRUNCATE);
        wcsncpy_s(nuevoUsuario->contrasena, contrasena, _TRUNCATE);
        wcsncpy_s(nuevoUsuario->nombre, nombre, _TRUNCATE);
        wcsncpy_s(nuevoUsuario->genero, genero, _TRUNCATE);
        wcsncpy_s(nuevoUsuario->foto, MAX_PATH, foto, _TRUNCATE);
        wcsncpy_s(nuevoUsuario->fechaNacimiento, MAX_PATH, fechaNacimiento, _TRUNCATE);


        if (loggeado != nullptr && loggeado->dato != nullptr) {
            wcscpy_s(nuevoUsuario->Admus, 50, loggeado->dato->Admus);
        }

        nuevoUsuario->uyear = uyear;
        nuevoUsuario->uday = uday;
        nuevoUsuario->umonth = umonth;

        nuevoUsuario->siguiente = nullptr;

        if (inicio == nullptr) {
            inicio = nuevoUsuario;
            fin = nuevoUsuario;
        }
        else {
            if (fin == nullptr) {
                inicio->siguiente = nuevoUsuario;
                nuevoUsuario->anterior = inicio;
            }
            else {
                nuevoUsuario->anterior = fin;
                fin->siguiente = nuevoUsuario;
            }

            fin = nuevoUsuario;
            nuevoUsuario->siguiente = nullptr; 
        }
    }

    Usuario* primerUsuario;
    Usuario* ultimoUsuario;

};

ListaVuelos;
ListaUsuarios;
LISTA_ADMUSUARIOS listaAdmUsuario;
//LISTA_USUARIOS listaUsuario;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//PRINCIPAL
LRESULT CALLBACK    PrincipalCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); 
//LISTA DE USUARIOS
LRESULT CALLBACK ListaUsuariosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//LISTA DE VUELOS
LRESULT CALLBACK ListaVuelosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//REGISTRAR ADMINISTRADOR
LRESULT CALLBACK RegistroAdminCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//LISTA DE PASAJEROS
LRESULT CALLBACK ListaPasajerosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//MANIFIESTO
LRESULT CALLBACK ManifiestoCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//REPORTE DE VUELOS
LRESULT CALLBACK ReporteVueloCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//REGISTRAR USUARIOS
LRESULT CALLBACK RegistroUsuariosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//LISTA DE PASES DE ABORDAJE
LRESULT CALLBACK ListaPasesCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//CANCELACION
LRESULT CALLBACK CancelacionesCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//REGISTRAR PASAJERO
LRESULT CALLBACK RegistroPasajeroCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//BOLETOOOOO
LRESULT CALLBACK BoletoCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//PASE DE ABORDAR
LRESULT CALLBACK PaseDeAbordarCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//REGISTRAR UN VUELO
LRESULT CALLBACK RegistroVueloCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// LISTA DE REPORTE DE VUELOS
LRESULT CALLBACK ListaReporteVueloCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
// INFORMACION DEL MANIFIESTO
LRESULT CALLBACK InfoManifiestoCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//DATOS VUELO
LRESULT CALLBACK DATOSVUELOCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//DATOS DEL USUARIO
LRESULT CALLBACK DATOSUSUARIOCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
//MENU
bool menu(int opcion, HWND hWnd);

NODO_AdmUsuario* buscarAdminPorUsuario(WCHAR* buscar);
Usuario* buscarEmpleadoPorUsuario(WCHAR const* nombreUsuario);
Vuelo* buscarVueloPorNumeroVuelo(WCHAR const* Numero);
void agregarAdmInicio(AdmUsuario* dato);
AdmUsuario* crearAdmUsuario(const WCHAR* Admusuario, const WCHAR* Admcorreo, const WCHAR* Admcontrasena, const WCHAR* Admnombre, const WCHAR* Admgenero, const WCHAR* Admfoto, const WCHAR* AdmfechaNacimiento, int year, int month, int day);
void agregarUsuarioALista(AdmUsuario* admUsuario, Usuario* usuario);

HBITMAP RutaDeFoto = nullptr;
bool obtenerRutaDeFoto(WCHAR* rutaFoto, DWORD longitudMaxima);
WCHAR AdmFoto[MAX_PATH] = L"";
WCHAR foto[MAX_PATH] = L"";
void ActualizarEtiquetaVuelo(HWND hListaVuelos, Vuelo* vuelo);
void ActualizarListBoxParaVueloConfirmado(HWND hListBox, const std::wstring& numeroVuelo);
std::wstring GenerarNumeroVuelo();

void swapVuelos(Vuelo*& v1, Vuelo*& v2);
Vuelo* partition(Vuelo* low, Vuelo* high);
void quickSortVuelos(Vuelo* low, Vuelo* high);
void acomodarVuelos(Vuelo*& head);


Vuelo* buscarVueloPorNumeroVuelo(WCHAR const* Numero) {
    ListaVuelos lista;
    lista.inicio = nullptr;

    Vuelo* temp = lista.inicio;
    while (temp != nullptr) {
        if (wcscmp(temp->numeroVuelo, Numero) == 0) {
            return temp; // Se encontró el usuario
        }
        temp = temp->siguiente;
    }
    return nullptr; // No se encontró el usuario
}

ListaUsuarios listaUsuarios; 
ListaVuelos listaVuelos;
 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PIAESTRUCTURAS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
    
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PIAESTRUCTURAS));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PIAESTRUCTURAS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PIAESTRUCTURAS);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REGISTRARVUELO), NULL, RegistroVueloCallback);
 /*  HWND hWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LOGIN), NULL, WndProc);*/
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG: {
        SendMessage(GetDlgItem(hWnd, IDC_LOGCOMB), CB_INSERTSTRING,  0, (LPARAM)L"EMPLEADO");
        SendMessage(GetDlgItem(hWnd, IDC_LOGCOMB), CB_INSERTSTRING,  0,(LPARAM)TEXT("ADMINISTRADOR"));
        
    }break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case IDC_LOGOK: {
                
                HWND hwndIdc_Comb = GetDlgItem(hWnd, IDC_LOGCOMB); 

                // Verificar si se obtuvo correctamente el identificador del ComboBox
                if (hwndIdc_Comb != NULL) {
                    
                    int index = SendMessage(hwndIdc_Comb, CB_GETCURSEL, 0, 0);

                    if (index != CB_ERR) { 
                      
                        int textLength = SendMessage(hwndIdc_Comb, CB_GETLBTEXTLEN, index, 0);

                        if (textLength != CB_ERR) { 
                            TCHAR* buffer = new TCHAR[textLength + 1];

                            
                            SendMessage(hwndIdc_Comb, CB_GETLBTEXT, index, (LPARAM)buffer);

                            
                            if (_tcscmp(buffer, _T("EMPLEADO")) == 0) {
                               
                                WCHAR us[100] = { 0 };
                                GetDlgItemText(hWnd, IDC_LOGUS, us, 100);

                                WCHAR contrasena[100] = { 0 };
                                GetDlgItemText(hWnd, IDC_LOGCON, contrasena, 100);

                                Usuario* usuarioEncontrado = buscarEmpleadoPorUsuario(us);

                                if (usuarioEncontrado != nullptr) {
                                    if (wcscmp(usuarioEncontrado->us, us) == 0 && wcscmp(usuarioEncontrado->contrasena, contrasena) == 0) {
                                        // Las credenciales son correctas
                                        logUsuario = usuarioEncontrado;
                                        HWND ventana =
                                            CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
                                        ShowWindow(ventana, SW_SHOW);
                                        EndDialog(hWnd, 0);
                                        /*MessageBox(hWnd, L"Inicio de sesión exitoso", L"Éxito", MB_OK | MB_ICONINFORMATION)*/
                                    }
                                    else {
                                        // Contraseña incorrecta
                                        int res = MessageBox(hWnd, L"Usuario o contrase\u00F1a incorrecta", L"USUARIO O CONTRASEÑA INCORRECTOS", MB_OKCANCEL | MB_ICONASTERISK);

                                    }

                                }
                                else {
                                    // Usuario no encontrado
                                    int res = MessageBox(hWnd, L"EMPLEADO NO ENCONTRADO", L"ERROR", MB_OKCANCEL | MB_ICONQUESTION);

                                }

                            }
                            if (_tcscmp(buffer, _T("ADMINISTRADOR")) == 0) {
                               
                                WCHAR Admus[100] = { 0 };
                                GetDlgItemText(hWnd, IDC_LOGUS, Admus, 100);

                                WCHAR Admcontrasena[100] = { 0 };
                                GetDlgItemText(hWnd, IDC_LOGCON, Admcontrasena, 100);

                                NODO_AdmUsuario* nodoAdmUsuario = buscarAdminPorUsuario(Admus);

                                if (nodoAdmUsuario != nullptr) {
                                    if (wcscmp(nodoAdmUsuario->dato->Admus, Admus) == 0 && wcscmp(nodoAdmUsuario->dato->Admcontrasena, Admcontrasena) == 0) {
                                        // Las credenciales son correctas
                                        loggeado = nodoAdmUsuario;
                                        HWND ventana =
                                            CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
                                        ShowWindow(ventana, SW_SHOW);
                                        EndDialog(hWnd, 0);
                                        /*MessageBox(hWnd, L"Inicio de sesión exitoso", L"Éxito", MB_OK | MB_ICONINFORMATION)*/
                                    }
                                    else {
                                        // Contraseña incorrecta
                                        int res = MessageBox(hWnd, L"Usuario o contrase\u00F1a incorrecta", L"USUARIO O CONTRASEÑA INCORRECTOS", MB_OKCANCEL | MB_ICONASTERISK);

                                    }

                                }
                                else {
                                    // Usuario no encontrado
                                    int res = MessageBox(hWnd, L"ADMINISTRADOR NO ENCONTRADO", L"ERROR", MB_OKCANCEL | MB_ICONQUESTION);

                                }
                            
                            }
                           
                            delete[] buffer;
                        }
                    }
                    else {
                        int res = MessageBox(hWnd, L"SELECCIONA UN TIPO DE USUARIO", L"ERROR", 0 | MB_ICONQUESTION);
                    }
                }

                
               
            }break;
            case IDC_REGISTROADMIN: {  
                HWND ventana =
                    CreateDialog(hInst, MAKEINTRESOURCE(IDD_REGISTRARADMIN), hWnd, RegistroAdminCallback); 
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }break;
            case IDM_EXIT: {
                DestroyWindow(hWnd);
                break;
            }default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...
            EndPaint(hWnd, &ps);
        }
        break;

    case WM_CLOSE:
        // En el mensaje de cierre de ventana, llamar a la función de cierre seguro
        DestroyWindow(hWnd);

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
   /* default:
        return DefWindowProc(hWnd, message, wParam, lParam);*/
    }
    return 0;
}

LRESULT CALLBACK PrincipalCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {

    case WM_INITDIALOG: {
        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NPRINCIPAL, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {
                    SetDlgItemText(hWnd, IDC_FPRINCIPAL, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FPRINCIPAL), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }
                
            }
          
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NPRINCIPAL, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {
                    SetDlgItemText(hWnd, IDC_FPRINCIPAL, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FPRINCIPAL), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }
              
            }
          
        }

    }break;

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case IDC_P1: {


            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAUSUARIOS), hWnd, ListaUsuariosCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);

        }break;
        case IDC_P2: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAVUELOS), hWnd, ListaVuelosCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
           

        }break;
        case IDC_P3: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAPASAJEROS), hWnd, ListaPasajerosCallback); 
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);            
        }break;
        case IDC_P4: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_CANCELACIONES), hWnd, CancelacionesCallback); 
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0); 
        }break;
        case IDC_P5: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTA_PASES), hWnd, ListaPasesCallback);  
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case IDC_P6: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_MANIFIESTO), hWnd, ManifiestoCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);            
        }break;
        case IDC_P7: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_REPORTEVUELOS), hWnd, ReporteVueloCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        }
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }
     
    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
   
    }
    return FALSE;
}

LRESULT CALLBACK ListaUsuariosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NLUSUARIOS, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350]; 
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLUSUARIOS, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLUSUARIOS), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen); 
                }                                     //a
                
            }                           //a
          
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NLUSUARIOS, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLUSUARIOS, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLUSUARIOS), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
                
            }                    
           
        }
        ind = listaUsuarios.inicio;
        HWND hListaUsuarios = GetDlgItem(hWnd, IDC_LUSUARIOS); 

        while (ind != NULL) {
            // Agregar el número de vuelo al ListBox
            SendMessage(hListaUsuarios, LB_ADDSTRING, NULL, (LPARAM)ind->nombre);

            // Mover al siguiente vuelo en la lista
            ind = ind->siguiente;
        }

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE; 
        }
        switch (wmId) {

        case IDC_LUSUARIOS: 
        {
            switch (HIWORD(wParam)) {
            case LBN_DBLCLK: {
                
                WCHAR texto[50] = { 0 };
                int seleccion = 0;
                seleccion = SendDlgItemMessage(hWnd, IDC_LUSUARIOS, LB_GETCURSEL, 0, 0);
                SendDlgItemMessage(hWnd, IDC_LUSUARIOS, LB_GETTEXT, seleccion, (LPARAM)texto); 
                cu = listaUsuarios.inicio;

                while (cu != NULL && wcscmp(texto, cu->nombre) != 0) {
                    cu = cu->siguiente;
                }

                if (cu != NULL && wcscmp(texto, cu->nombre) == 0) { 
                    HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DATOSUSUARIO), hWnd, DATOSUSUARIOCallback); 
                    ShowWindow(ventana, SW_SHOW);
                    EndDialog(hWnd, 0);
                }



            }
                           break;
            }
        }
                        break;

        case IDC_LVUELOS: {
            switch (HIWORD(wParam)) 
            {
            case LBN_DBLCLK: 
            {
                // Handle double-click on flight
                WCHAR texto[50] = { 0 }; // Change tipo and ensure to include <Windows.h> for WCHAR definition
                int seleccion = 0;
                seleccion = SendDlgItemMessage(hWnd, IDC_LUSUARIOS, LB_GETCURSEL, 0, 0);
                SendDlgItemMessage(hWnd, IDC_LVUELOS, LB_GETTEXT, seleccion, (LPARAM)texto);
                ci = listaVuelos.inicio;

                while (ci != NULL && wcscmp(texto, ci->numeroVuelo) != 0) {
                    ci = ci->siguiente;
                }

                if (ci != NULL && wcscmp(texto, ci->numeroVuelo) == 0) {
                    HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DATOSUSUARIO), hWnd, DATOSUSUARIOCallback);
                    ShowWindow(ventana, SW_SHOW);
                    EndDialog(hWnd, 0);
                }



            }break;
            }
        }break;

        case IDC_AGREGARUS: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_REGISTRO), hWnd, RegistroUsuariosCallback); 
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0); 
        }break;
        case ID_LUREGRESAR: { 
            HWND ventana = 
            CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            ShowWindow(ventana, SW_SHOW); 
            EndDialog(hWnd, 0);
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK ListaVuelosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NLVUELOS, loggeado->dato->Admus);
        
        if (AdmFoto != nullptr)
        {
            WCHAR ruta[350];
            wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
            HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
            if (imagen != NULL) {      //a
                SetDlgItemText(hWnd, IDC_FLVUELOS, ruta);
                SendMessage(GetDlgItem(hWnd, IDC_FLVUELOS), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
            }                                     //a
           
        }

        }

      if (logUsuario != nullptr) {
      SetDlgItemText(hWnd, IDC_NLVUELOS, logUsuario->dato->us);
        if (AdmFoto != nullptr)
        {
           WCHAR ruta[350];
           wcscpy_s(ruta, 350, logUsuario->dato->foto);
           HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
           if (imagen != NULL) 
           {      //a
              SetDlgItemText(hWnd, IDC_FLVUELOS, ruta);
              SendMessage(GetDlgItem(hWnd, IDC_FLVUELOS), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
           }                                //a
              
        }                          //a

      }
   
      indice = listaVuelos.inicio;

      // Obtener el control de lista
      HWND hListaVuelos = GetDlgItem(hWnd, IDC_LVUELOS);

      while (indice != NULL) {
          
          std::wstring numeroVuelo = indice->numeroVuelo;

          std::wstring texto = L"Pendiente - " + numeroVuelo;

          SendMessage(hListaVuelos, LB_ADDSTRING, NULL, (LPARAM)texto.c_str());

          indice = indice->siguiente; 
      }


    } break;

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case IDC_LVUELOS: {
            switch (HIWORD(wParam)) {
            case LBN_DBLCLK: {
                
                WCHAR texto[50] = { 0 };
                int seleccion = 0;
                seleccion = SendDlgItemMessage(hWnd, IDC_LVUELOS, LB_GETCURSEL, 0, 0);
                SendDlgItemMessage(hWnd, IDC_LVUELOS, LB_GETTEXT, seleccion, (LPARAM)texto);

                ci = listaVuelos.inicio;
                while (ci != nullptr) {
                    WCHAR* vueloParte = wcsstr(texto, L"Vuelo-");
                    if (vueloParte != nullptr && wcscmp(vueloParte, ci->numeroVuelo) == 0) {
                        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DATOSVUELO), hWnd, DATOSVUELOCallback);
                        ShowWindow(ventana, SW_SHOW);
                        EndDialog(hWnd, 0);
                        break; // Salir del bucle después de encontrar la coincidencia
                    }
                    ci = ci->siguiente; 
                }


              
            }
                           break;
            }
        }
                        break;
        case ID_LV_AGREGAR: {
            // Open dialog to register a flight
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REGISTRARVUELO), hWnd, RegistroVueloCallback);
            if (ventana != NULL) {
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }
                          break;
        case ID_LVREG: {
            // Return to the main menu
            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            if (ventana != NULL) {
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }
                     break;
        
        }
        break;
    }


    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}
//REGISTRO DE PASAJEROS
LRESULT CALLBACK RegistroPasajeroCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NAPASAJERO, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FAPASAJERO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FAPASAJERO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NAPASAJERO, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FAPASAJERO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FAPASAJERO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
               
            }                          //a
            
        }

        SendMessage(GetDlgItem(hWnd, IDC_AP3), CB_INSERTSTRING, 0, (LPARAM)L"HOMBRE");
        SendMessage(GetDlgItem(hWnd, IDC_AP3), CB_INSERTSTRING, 0, (LPARAM)TEXT("MUJER"));

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_PAGO: { 
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_BOLETO), hWnd, BoletoCallback);  
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case ID_RPREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAPASAJEROS), hWnd, ListaPasajerosCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        }
    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}

LRESULT CALLBACK RegistroAdminCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        SendMessage(GetDlgItem(hWnd, IDC_RA6), CB_INSERTSTRING, 0, (LPARAM)L"HOMBRE");
        SendMessage(GetDlgItem(hWnd, IDC_RA6), CB_INSERTSTRING, 0, (LPARAM)TEXT("MUJER"));

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {

        case IDC_RA7: {

            HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LOGIN), NULL, WndProc);
            ShowWindow(ventana, SW_SHOW); 
            EndDialog(hWnd, 0);
        }break;

        case IDC_BUSCAR: 
        {   
            if (obtenerRutaDeFoto(AdmFoto, MAX_PATH)) {
                HWND hImagen = GetDlgItem(hWnd, IDC_REGISFOTO);
                if (hImagen != NULL) {
                    SendMessage(hImagen, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadImage(NULL, AdmFoto, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
                }
            }
        }break;
        case ID_AGREGARAdm: {

            HWND hImagen = GetDlgItem(hWnd, IDC_REGISFOTO);  

            SYSTEMTIME fecha;
            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_RA5), &fecha);

            WCHAR AdmUsuario[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RA1, AdmUsuario, 50);

            WCHAR Admcorreo[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RA2, Admcorreo, 50);

            WCHAR Admcontrasena[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RA3, Admcontrasena, 50);

            WCHAR Admnombre[100] = { 0 };
            GetDlgItemText(hWnd, IDC_RA4, Admnombre, 100);

            WCHAR AdmfechaNacimiento[MAX_PATH] = { 0 };
            GetDlgItemText(hWnd, IDC_RA5, AdmfechaNacimiento, MAX_PATH);

            WCHAR Admgenero[100] = { 0 };
            GetDlgItemText(hWnd, IDC_RA6, Admgenero, 100);

            int dia = (fecha.wDay);
            int mes = (fecha.wMonth);
            int anio = (fecha.wYear);
            SYSTEMTIME currentDate;
            GetLocalTime(&currentDate);


            if (wcscmp(AdmUsuario, L"") == 0 || wcscmp(Admcorreo, L"") == 0 || wcscmp(Admcontrasena, L"") == 0 || wcscmp(Admnombre, L"") == 0 || wcscmp(Admgenero, L"") == 0) {
                MessageBox(hWnd, L"REGISTRO INCOMPLETO", L"INCOMPLETO", 0 | MB_ICONEXCLAMATION);
            }
            else {
               

                // Se pasa directamente AdmFoto, no su dirección
                agregarAdmInicio(crearAdmUsuario(AdmUsuario, Admcorreo, Admcontrasena, Admnombre, Admgenero, AdmFoto, AdmfechaNacimiento, anio, mes, dia));

                MessageBox(hWnd, L"REGISTRO COMPLETO ", L"COMPLETO", 0);
                HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LOGIN), NULL, WndProc); 
                ShowWindow(ventana, SW_SHOW);
                EndDialog(hWnd, 0);
            }
        }
        }
    }break;
    
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}

LRESULT CALLBACK ListaPasajerosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NLVUELOS, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLPASAJEROS, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLPASAJEROS), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
                
            }                           //a
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NLPASAJEROS, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLPASAJEROS, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLPASAJEROS), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
                
            }                          //a
            
        }

    }

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_AGREGARPASAJERO: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_AGREGARPASAJERO), hWnd, RegistroPasajeroCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case ID_LPREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK ManifiestoCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NMANIFIESTO, loggeado->dato->Admus); 
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FMANIFIESTO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FMANIFIESTO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a
         
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NMANIFIESTO, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FMANIFIESTO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FMANIFIESTO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
                
            }                          //a
          
        }

    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_MREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK ReporteVueloCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NREPORTE, loggeado->dato->Admus); 
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FREPORTE, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FREPORTE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
                
            }                           //a
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NREPORTE, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FREPORTE, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FREPORTE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
                
            }                          //a
          
        }

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_okMAN: { 
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAREPORTEVUELOS), hWnd, ListaReporteVueloCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case ID_RPREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK RegistroUsuariosCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NREGISTRO, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FREGISTRO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FREGISTRO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a
           
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NREGISTRO, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FREGISTRO, ruta); 
                    SendMessage(GetDlgItem(hWnd, IDC_FREGISTRO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
               
            }                          //a
            SetDlgItemText(hWnd, IDC_NREGISTRO, loggeado->dato->Admus);
        }

        SendMessage(GetDlgItem(hWnd, IDC_RU6), CB_INSERTSTRING, 0, (LPARAM)L"HOMBRE");
        SendMessage(GetDlgItem(hWnd, IDC_RU6), CB_INSERTSTRING, 0, (LPARAM)TEXT("MUJER"));

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        
        case IDC_BUSCAR1:
        {
            if (obtenerRutaDeFoto(foto, MAX_PATH)) {
                HWND hImagen = GetDlgItem(hWnd, IDC_REGISFOTO1);
                if (hImagen != NULL) {
                    SendMessage(hImagen, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)LoadImage(NULL, foto, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
                }
            }
        }break;
        
        case ID_AGREGAR: {

            HWND hImagen = GetDlgItem(hWnd, IDC_REGISFOTO1);

            SYSTEMTIME fecha;
            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_RU5), &fecha);

            WCHAR us[50] = { 0 }; 
            GetDlgItemText(hWnd, IDC_RU1, us, 50); 

            WCHAR correo[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RU2, correo, 50);

            WCHAR contrasena[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RU3, contrasena, 50);

            WCHAR nombre[100] = { 0 };
            GetDlgItemText(hWnd, IDC_RU4, nombre, 100);

            WCHAR fechaNacimiento[MAX_PATH] = { 0 };
            GetDlgItemText(hWnd, IDC_RU5, fechaNacimiento, MAX_PATH);

            WCHAR genero[100] = { 0 };
            GetDlgItemText(hWnd, IDC_RU6, genero, 100);

            int udia = (fecha.wDay);
            int umes = (fecha.wMonth);
            int uanio = (fecha.wYear);
            SYSTEMTIME currentDate;
            GetLocalTime(&currentDate);


            if (wcscmp(us, L"") == 0 || wcscmp(correo, L"") == 0 || wcscmp(contrasena, L"") == 0 || wcscmp(nombre, L"") == 0 || wcscmp(genero, L"") == 0) {
                MessageBox(hWnd, L"REGISTRO INCOMPLETO", L"INCOMPLETO", 0 | MB_ICONEXCLAMATION);

            }
            else {


                // Se pasa directamente AdmFoto, no su dirección
                listaUsuarios.agregarUsuario(us, correo, contrasena, nombre, fechaNacimiento, genero,foto, uanio, umes, udia);
                
                /*Usuario* nuevoUsuario = listaUsuarios.obtenerUltimoUsuario();*/
               /* agregarUsuarioALista(admin, uss); */

                MessageBox(hWnd, L"REGISTRO COMPLETO ", L"USUARIO REGISTRADO", 0);
                
            }
        }

        case ID_RUREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAUSUARIOS), hWnd, ListaUsuariosCallback);
            ShowWindow(ventana, SW_SHOW); 
            EndDialog(hWnd, 0); 
        };
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK ListaPasesCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NLPASES, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLPASES, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLPASES), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a

        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NLPASES, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLPASES, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLPASES), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
               
            }                          //a

        }

    }break;
    case WM_COMMAND: { 
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_LPAREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK CancelacionesCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NLCANCEL, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLCANCEL, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLCANCEL), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a
          
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NLCANCEL, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLCANCEL, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLCANCEL), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen); 
                }                                //a
              
            }                          //a
            
        }

    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }

        switch (wmId) {
        case ID_CREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK BoletoCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NBOLETO, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FBOLETO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FBOLETO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
                
            }                           //a
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NBOLETO, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FBOLETO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FBOLETO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
                
            }                          //a
           
        }

        SendMessage(GetDlgItem(hWnd, IDC_B1), CB_INSERTSTRING, 0, (LPARAM)L"TARJETA");
        SendMessage(GetDlgItem(hWnd, IDC_B1), CB_INSERTSTRING, 0, (LPARAM)TEXT("EFECTIVO"));
        SendMessage(GetDlgItem(hWnd, IDC_B2), CB_INSERTSTRING, 0, (LPARAM)L"EJECUTIVO");
        SendMessage(GetDlgItem(hWnd, IDC_B2), CB_INSERTSTRING, 0, (LPARAM)TEXT("TURISTA"));
    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }

        switch (wmId) {
        case ID_BPAGAR: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PASEABORDAR), hWnd, PaseDeAbordarCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case ID_BREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_AGREGARPASAJERO), hWnd, RegistroPasajeroCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK PaseDeAbordarCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_INITDIALOG:
    {
        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NPASE, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FPASE, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FPASE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a
           
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NPASE, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FPASE, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FPASE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
                
            }                          //a
            
        }

    }break;

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }

        switch (wmId) {
        case ID_PAREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_BOLETO), hWnd, BoletoCallback);
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK RegistroVueloCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NVUELO, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_RVUELO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_RVUELO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
             
            }                           //a
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NVUELO, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_RVUELO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_RVUELO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
              
            }                          //a
          
        }

    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }

        switch (wmId) {
        case REGISVUELO1: {
            SYSTEMTIME hora;
            SYSTEMTIME fecha;

            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_RV3), &fecha);

           /* DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_RV8), &fecha);*/

            DateTime_GetSystemtime(GetDlgItem(hWnd, IDC_RV9), &hora);

            WCHAR origen[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RV1, origen, 50);

            WCHAR destino[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RV2, destino, 50); 

            std::wstring numeroVuelo = GenerarNumeroVuelo(); 

            WCHAR asientosDisponibles[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RV5, asientosDisponibles, 50); 

            WCHAR turistas[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RV6, turistas, 50);

            WCHAR ejecutivo[50] = { 0 };
            GetDlgItemText(hWnd, IDC_RV7, ejecutivo, 50);

            WCHAR fechaSalida[MAX_PATH] = { 0 };
            GetDlgItemText(hWnd, IDC_RV3, fechaSalida, MAX_PATH);  

            WCHAR fecharegistro[MAX_PATH] = { 0 };
            GetDlgItemText(hWnd, IDC_RV8, fecharegistro, MAX_PATH);

            WCHAR horaregistro[MAX_PATH] = { 0 };
            GetDlgItemText(hWnd, IDC_RV9, horaregistro, MAX_PATH); 

            int horas = (hora.wHour);
            int minutos = (hora.wMinute);
            int segundos = (hora.wSecond); 
            int vdia = (fecha.wDay);
            int vmes = (fecha.wMonth);
            int vanio = (fecha.wYear);
            SYSTEMTIME currentDate;
            GetLocalTime(&currentDate);

            int total = wcstol(asientosDisponibles, nullptr, 10); 
            int turista = wcstol(turistas, nullptr, 10);
            int ejecutivos = wcstol(ejecutivo, nullptr, 10);

            if (turista + ejecutivos > total) {
                MessageBox(hWnd, L"CANTIDAD DE ASIENTOS INCONSISTENTE", L"ERROR", MB_ICONERROR);
            }
            else if (vanio < currentDate.wYear || (vanio == currentDate.wYear && vmes < currentDate.wMonth) ||
                (vanio == currentDate.wYear && vmes == currentDate.wMonth && vdia < currentDate.wDay)|| vanio == currentDate.wYear && vmes == currentDate.wMonth && vdia == currentDate.wDay) {
                MessageBox(hWnd, L"FECHA INVALIDA", L"ERROR", MB_ICONERROR); 
            }
            else if (wcscmp(origen, L"") == 0  || wcscmp(asientosDisponibles, L"") == 0 || wcscmp(turistas, L"") == 0 || wcscmp(ejecutivo, L"") == 0) { 
                MessageBox(hWnd, L"INCOMPLETO", L"vuelo incompleto", 0 | MB_ICONEXCLAMATION);

            }
            else {


                // Se pasa directamente AdmFoto, no su dirección
                listaVuelos.agregarVuelo(origen, destino, numeroVuelo.c_str(), asientosDisponibles, turistas, ejecutivo,fecharegistro, horaregistro, horas, minutos, segundos, fechaSalida, vdia, vmes, vanio);

              /*  MessageBox(hWnd, L"REGISTRO DE VUELO COMPLETADO ", L"COMPLETADO", 0);*/
                MessageBox(hWnd, numeroVuelo.c_str(), L"VUELO NUMERO", MB_OK); 
               
            }

        }

        case ID_RVREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_PRINCIPAL), hWnd, PrincipalCallback); 
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0); 
        }break;

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK ListaReporteVueloCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {

    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NLREPORTE, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLREPORTE, ruta); 
                    SendMessage(GetDlgItem(hWnd, IDC_FLREPORTE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
              
            }                           //a
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NLREPORTE, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FLREPORTE, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FLREPORTE), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
               
            }                          //a
           
        }

    }

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }

        switch (wmId) {
        case ID_LRVREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_REPORTEVUELOS), hWnd, ReporteVueloCallback);
            ShowWindow(ventana, SW_SHOW); 
            EndDialog(hWnd, 0); 
        }break;
        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK InfoManifiestoCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NINFOMANI, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      
                    SetDlgItemText(hWnd, IDC_FINFOMANI, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FINFOMANI), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                    
               
            }                          
            
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NINFOMANI, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FINFOMANI, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FINFOMANI), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
               
            }                          //a
        
        }

    }
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_IMREG: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_MANIFIESTO), hWnd, ManifiestoCallback);
            ShowWindow(ventana, SW_SHOW); 
            EndDialog(hWnd, 0); 
        }break;

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK DATOSVUELOCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { 
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NDVUELO, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FDVUELO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FDVUELO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                     //a
               
            }                           //a
          
        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NDVUELO, logUsuario->dato->us);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FDVUELO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FDVUELO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                //a
               
            }                          //a
           
        }

      /*  ci = listaVuelos.inicio;*/
    
        SetDlgItemText(hWnd, IDC_DV1, ci->origen);
        SetDlgItemText(hWnd, IDC_DV2, ci->destino);
        SetDlgItemText(hWnd, IDC_DV3, ci->fechaSalida);
        WCHAR* numeroVueloWCHAR = ci->numeroVuelo; // Suponiendo que ci->numeroVuelo es de tipo WCHAR*
        std::wstring numeroVueloString(numeroVueloWCHAR);
        SetDlgItemText(hWnd, IDC_DV4, numeroVueloString.c_str());
        SetDlgItemText(hWnd, IDC_DV5, ci->asientosDisponibles);
        SetDlgItemText(hWnd, IDC_DV6, ci->turistas);
        SetDlgItemText(hWnd, IDC_DV8, (ci->fecharegistro));
        SetDlgItemText(hWnd, IDC_DV9, (ci->horaregistro));
        SetDlgItemText(hWnd, IDC_DV7, ci->ejecutivo);
       

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case IDC_REGINFOV: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAVUELOS), hWnd, ListaVuelosCallback);  
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;
        case IDC_CANCELVUELO: {

        }break;
        case IDC_CONFIRMAR: {
            ci->estado = Confirmado;
            WCHAR* numeroVueloWCHAR = ci->numeroVuelo; 

            /*const WCHAR* numeroVueloWCHAR = ci->numeroVuelo.c_str();*/


            ActualizarListBoxParaVueloConfirmado(hListaVuelos, ci->numeroVuelo);
  
            MessageBox(hWnd, L"El vuelo ha sido confirmado.", L"Confirmación de vuelo", MB_OK | MB_ICONINFORMATION);
           

        }break;

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

LRESULT CALLBACK DATOSUSUARIOCallback(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_INITDIALOG: {

        if (loggeado != nullptr) {
            SetDlgItemText(hWnd, IDC_NDUSUARIO, loggeado->dato->Admus);
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, loggeado->dato->Admfoto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FDUSUARIO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FDUSUARIO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                                    

            }                           

        }

        if (logUsuario != nullptr) {
            SetDlgItemText(hWnd, IDC_NDUSUARIO, logUsuario->dato->us); 
            if (AdmFoto != nullptr)
            {
                WCHAR ruta[350];
                wcscpy_s(ruta, 350, logUsuario->dato->foto);
                HBITMAP imagen = (HBITMAP)LoadImage(hInst, ruta, IMAGE_BITMAP, 20, 20, LR_DEFAULTCOLOR | LR_DEFAULTSIZE | LR_LOADFROMFILE);
                if (imagen != NULL) {      //a
                    SetDlgItemText(hWnd, IDC_FDUSUARIO, ruta);
                    SendMessage(GetDlgItem(hWnd, IDC_FDUSUARIO), STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)imagen);
                }                             

            }                          

        }

        /*  ci = listaVuelos.inicio;*/

        SetDlgItemText(hWnd, IDC_DU1, cu->us);
        SetDlgItemText(hWnd, IDC_DU2, cu->correo);
        SetDlgItemText(hWnd, IDC_DU3, cu->contrasena);
        SetDlgItemText(hWnd, IDC_DU4, cu->nombre);
        SetDlgItemText(hWnd, IDC_DU5, cu->fechaNacimiento);
        SetDlgItemText(hWnd, IDC_DU6, cu->genero);

    }break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        if (menu(wmId, hWnd)) {
            return FALSE;
        }
        switch (wmId) {
        case ID_MODUS: {
            HWND ventana =
                CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAUSUARIOS), hWnd, ListaUsuariosCallback);  
            ShowWindow(ventana, SW_SHOW);
            EndDialog(hWnd, 0);
        }break;

        }

    }break;
    case WM_CLOSE: {

        int res = MessageBox(hWnd, L"¿Realmente deseas salir?", L"ALERTA", MB_OKCANCEL | MB_ICONWARNING);

        if (res == IDOK)
        {
            EndDialog(hWnd, 0);
            DestroyWindow(hWnd);
        }

    }break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    }
    return FALSE;
}

bool menu(int opcion, HWND hWnd) {
    switch (opcion) {
    case ID_GESTIONDEUSUARIOS_REGISTRARUSUARIO32779: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REGISTRO), hWnd, RegistroUsuariosCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_GESTIONDEUSUARIOS_VERLISTADEUSUARIOS32780: {
        HWND ventana = CreateDialog(hInst,MAKEINTRESOURCE(IDD_LISTAUSUARIOS), hWnd, ListaUsuariosCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_MENU_VUELOS: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAVUELOS), hWnd, ListaVuelosCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID_MENU_PASAJEROS: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTAPASAJEROS), hWnd, ListaPasajerosCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;

    case ID_MENU_CANCELACIONES: {
        HWND ventana =  CreateDialog(hInst, MAKEINTRESOURCE(IDD_CANCELACIONES), hWnd, CancelacionesCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;

    case ID_MENU_PASESDEABORDAR: { 
        HWND ventana =  CreateDialog(hInst, MAKEINTRESOURCE(IDD_LISTA_PASES), hWnd, ListaPasesCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;

    case ID_MENU_MANIFIESTO: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MANIFIESTO), hWnd, ManifiestoCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    case ID__MENU_REPORTEDEVUELOS: {
        HWND ventana = CreateDialog(hInst, MAKEINTRESOURCE(IDD_REPORTEVUELOS), hWnd, ReporteVueloCallback);
        ShowWindow(ventana, SW_SHOW);
        EndDialog(hWnd, 0);
    }break;
    default: return false;
    }
    return true;
}

class ArbolPasajeros {
private:
    Pasajero* raiz;


    Pasajero* agregarPasajeroRecursivo(Pasajero* nodo, WCHAR tipoVuelo, WCHAR usuario, WCHAR nombre, WCHAR fechaNacimiento, WCHAR genero, WCHAR nacionalidad, int numeroBoleto) {
        if (nodo == nullptr) {
            Pasajero* nuevoPasajero = new Pasajero;
            nuevoPasajero->tipoVuelo = tipoVuelo;
            nuevoPasajero->usuario = usuario;
            nuevoPasajero->nombre = nombre;
            nuevoPasajero->fechaNacimiento = fechaNacimiento;
            nuevoPasajero->genero = genero;
            nuevoPasajero->nacionalidad = nacionalidad;
            nuevoPasajero->numeroBoleto = numeroBoleto;
            nuevoPasajero->izquierda = nullptr;
            nuevoPasajero->derecha = nullptr;
            return nuevoPasajero;
        }


        if (numeroBoleto < nodo->numeroBoleto)
            nodo->izquierda = agregarPasajeroRecursivo(nodo->izquierda, tipoVuelo, usuario, nombre, fechaNacimiento, genero, nacionalidad, numeroBoleto);
        else
            nodo->derecha = agregarPasajeroRecursivo(nodo->derecha, tipoVuelo, usuario, nombre, fechaNacimiento, genero, nacionalidad, numeroBoleto);


        return nodo;
    }
    Pasajero* buscarPorBoletoRecursivo(Pasajero* nodo, int numeroBoleto) {
        if (nodo == nullptr || nodo->numeroBoleto == numeroBoleto)
            return nodo;


        if (numeroBoleto < nodo->numeroBoleto)
            return buscarPorBoletoRecursivo(nodo->izquierda, numeroBoleto);


        return buscarPorBoletoRecursivo(nodo->derecha, numeroBoleto);
    }
public:
    ArbolPasajeros() : raiz(nullptr) {}


    void agregarPasajero(WCHAR tipoVuelo, WCHAR usuario, WCHAR nombre, WCHAR fechaNacimiento, WCHAR genero, WCHAR nacionalidad, int numeroBoleto) 
    {
        raiz = agregarPasajeroRecursivo(raiz, tipoVuelo, usuario, nombre, fechaNacimiento, genero, nacionalidad, numeroBoleto);
    }
        Pasajero* buscarPorBoleto(int numeroBoleto) 
        {
            return buscarPorBoletoRecursivo(raiz, numeroBoleto);
        }
    
};

NODO_AdmUsuario* buscarAdminPorUsuario(WCHAR* buscar) { 
   
    NODO_AdmUsuario* actual = listaAdmUsuario.origen; 

    while (actual != nullptr) {
        if (wcscmp(actual->dato->Admus, buscar) == 0 || wcscmp(actual->dato->Admus, buscar) == 0) {
            return actual;
        }
        actual = actual->next;
    }

    return nullptr;
}

// Agrega métodos para buscar, eliminar, mostrar usuarios, etc.
void swapUsuarios(Usuario*& u1, Usuario*& u2) {
    Usuario* temp = u1;
    u1 = u2;
    u2 = temp;
}

Usuario* partition(Usuario* low, Usuario* high) {
    const WCHAR* pivot = high->nombre;
    Usuario* i = low->anterior;

    for (Usuario* j = low; j != high; j = j->siguiente) {
        if (wcscmp(j->nombre, pivot) <= 0) {
            i = (i == nullptr) ? low : i->siguiente;
            swapUsuarios(i, j);
        }
    }
    i = (i == nullptr) ? low : i->siguiente;
    swapUsuarios(i, high);
    return i;
}

Usuario* buscarEmpleadoPorUsuario(WCHAR const* nombreUsuario) {
    ListaUsuarios lista;
    lista.inicio = nullptr;
    
    Usuario* temp = lista.inicio;
    while (temp != nullptr) {
        if (wcscmp(temp->us, nombreUsuario) == 0) {
            return temp; // Se encontró el usuario
        }
        temp = temp->siguiente;
    }
    return nullptr; // No se encontró el usuario
}

void quickSortUsuarios(Usuario* low, Usuario* high) {
    if (high != nullptr && low != high && low != high->siguiente) {
        Usuario* pivot = partition(low, high);
        quickSortUsuarios(low, pivot->anterior);
        quickSortUsuarios(pivot->siguiente, high);
    }
}

void acomodarUsuarios(Usuario*& head) {
    Usuario* temp = head;
    while (temp && temp->siguiente) {
        temp->siguiente->anterior = temp;
        temp = temp->siguiente;
    }
    quickSortUsuarios(head, temp);
}

NODO_AdmUsuario* nuevoNodo(AdmUsuario* dato) {
    NODO_AdmUsuario* nuevoNodoAdmusuario = new NODO_AdmUsuario();
    nuevoNodoAdmusuario->dato = dato;
    nuevoNodoAdmusuario->next = nullptr;
    nuevoNodoAdmusuario->ante = nullptr;

    return nuevoNodoAdmusuario;
}

void agregarAdmInicio(AdmUsuario* dato)
{ 
    NODO_AdmUsuario* nuevoNodoAdmusuario = nuevoNodo(dato);

    if (listaAdmUsuario.origen == nullptr) {
        listaAdmUsuario.origen = nuevoNodoAdmusuario;
        listaAdmUsuario.fin = nuevoNodoAdmusuario;
        nuevoNodoAdmusuario->next = nullptr;
    }
    else {
        nuevoNodoAdmusuario->next = listaAdmUsuario.origen;
        listaAdmUsuario.origen->ante = nuevoNodoAdmusuario;
        listaAdmUsuario.origen = nuevoNodoAdmusuario;
    }
}

AdmUsuario* crearAdmUsuario(const WCHAR* Admus, const WCHAR* Admcorreo, const WCHAR* Admcontrasena, const WCHAR* Admnombre, const WCHAR* Admgenero, const WCHAR* Admfoto, const WCHAR* AdmfechaNacimiento,int day, int month, int year) 
{
    
    AdmUsuario* nuevoAdmUsuario = new AdmUsuario;
    wcsncpy_s(nuevoAdmUsuario->Admus, Admus, _TRUNCATE);
    wcsncpy_s(nuevoAdmUsuario->Admcorreo, Admcorreo, _TRUNCATE);
    wcsncpy_s(nuevoAdmUsuario->Admcontrasena, Admcontrasena, _TRUNCATE);
    wcsncpy_s(nuevoAdmUsuario->Admnombre, Admnombre, _TRUNCATE);
    wcsncpy_s(nuevoAdmUsuario->Admgenero, Admgenero, _TRUNCATE);
    wcsncpy_s(nuevoAdmUsuario->Admfoto, MAX_PATH, Admfoto, _TRUNCATE);
    wcsncpy_s(nuevoAdmUsuario->AdmfechaNacimiento, MAX_PATH, AdmfechaNacimiento, _TRUNCATE);
    nuevoAdmUsuario->day = day;
    nuevoAdmUsuario->month = month;
    nuevoAdmUsuario->year = year;
    
    nuevoAdmUsuario->listaUsuarios = nullptr; 

    nuevoAdmUsuario->siguiente = nullptr;
    return nuevoAdmUsuario;
}

bool obtenerRutaDeFoto(WCHAR* rutaFoto, DWORD longitudMaxima) {
    OPENFILENAME ofn;
    WCHAR szFile[MAX_PATH] = L"";

    // Inicializar la estructura OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL; // La ventana principal, si la tienes
    ofn.lpstrFilter = L"Archivos de imagen (*.bmp;*.jpg;*.png)\0*.BMP;*.JPG;*.PNG\0Todos los archivos (*.*)\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    // Mostrar el cuadro de diálogo para abrir archivos
    if (GetOpenFileName(&ofn) == TRUE) {
        wcsncpy_s(rutaFoto, longitudMaxima, szFile, _TRUNCATE);
        return true; // Se seleccionó una foto
    }
    return false; // El usuario canceló la selección
}

void agregarUsuarioALista(AdmUsuario* admUsuario, Usuario* usuario) {
    if (admUsuario->listaUsuarios == nullptr) {
        admUsuario->listaUsuarios = usuario;
    }
    else {
        // Busca el último Usuario en la lista y agrega el nuevo Usuario al final
        Usuario* ultimoUsuario = admUsuario->listaUsuarios;
        while (ultimoUsuario->siguiente != nullptr) {
            ultimoUsuario = ultimoUsuario->siguiente;
        }
        ultimoUsuario->siguiente = usuario;
        usuario->anterior = ultimoUsuario;
    }
}

void ActualizarEtiquetaVuelo(HWND hListaVuelos, Vuelo* vuelo) { 
    const wchar_t* etiqueta = L"Pendiente";
    switch (vuelo->estado) { 
    case Confirmado:
        etiqueta = L"Confirmado";
        break;
    case Cancelado:
        etiqueta = L"Cancelado";
        break;
    default:
        break;
    }
    std::wstring texto = std::wstring(vuelo->numeroVuelo) + L" - " + etiqueta;

    SendMessage(hListaVuelos, LB_ADDSTRING, NULL, (LPARAM)texto.c_str());
}

void ActualizarListBoxParaVueloConfirmado(HWND hListBox, const std::wstring& numeroVuelo) {
    // Obtener la cantidad de elementos en el ListBox
    int itemCount = SendMessage(hListBox, LB_GETCOUNT, 0, 0);

    // Recorrer todos los elementos del ListBox
    for (int i = 0; i < itemCount; ++i) {
        // Obtener el texto del elemento actual
        wchar_t buffer[256]; // Suponiendo un tamaño máximo de 256 caracteres
        SendMessage(hListBox, LB_GETTEXT, i, reinterpret_cast<LPARAM>(buffer));

        // Verificar si el texto del elemento actual contiene el número de vuelo
        if (wcsstr(buffer, numeroVuelo.c_str()) != nullptr) {
            // Si coincide, actualiza el texto del elemento para reflejar el nuevo estado del vuelo
            std::wstring nuevoTexto = L"Confirmado - " + numeroVuelo;
            SendMessage(hListBox, LB_DELETESTRING, i, 0); // Elimina el elemento actual
            SendMessage(hListBox, LB_INSERTSTRING, i, reinterpret_cast<LPARAM>(nuevoTexto.c_str())); // Inserta el nuevo elemento
            break; // Sal del bucle una vez que se haya actualizado el ListBox
        }
    }
}

std::wstring GenerarNumeroVuelo() {
    // Incrementar el contador de vuelos
    numeroVueloActual++;

    // Convertir el contador a una cadena de caracteres amplios (wstring)
    std::wstringstream ss;
    ss << L"Vuelo-" << numeroVueloActual;
    return ss.str();
}