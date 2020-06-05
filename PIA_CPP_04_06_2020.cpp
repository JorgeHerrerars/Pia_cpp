#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <string>
using namespace std;


struct Contacto{
    int userid;
    int id;
    string nombre;
    long long celular;
    long long telefonoC;
    long long telefonoT;
    string correo;
    string direccion;
    string descrip;
};
//PROTOTIPO DE OPERADORES DE CONTACTO
istream& operator>> (istream&,Contacto&);
ostream& operator<< (ostream&,Contacto&);
//CLASE USUARIO (INCLUYE FUNCIONES PARA SUS CONTACTOS)
class Usuario{
private:
    int id;
    string user;
    string pass;
    vector <Contacto> contactos;
public:
    Usuario(){}
    void setId(int id){
        this -> id = id;
    }
    int getId(){
        return id;
    }
    void setUser(string user){
        this -> user = user;
    }
    string getUser(){
        return user;
    }
    void setPass(string pass){
        this -> pass = pass;
    }
    string getPass(){
        return pass;
    }
    void setContactos(vector <Contacto> contactos){
        this -> contactos = contactos;
    }
    vector <Contacto> getContactos(){
        return contactos;
    }
    void mostrarContactos(){
        for(Contacto c: contactos){
            cout << c << endl;
        }
    }
    vector <Contacto> agregarContacto(){
        vector <Contacto> nuevos = contactos;
        Contacto nuevo;
        cin >> nuevo;
        if(contactos.empty()){
            nuevo.id = 1;
        }else{
            nuevo.id = contactos[contactos.size()-1].id+1;
        }
        nuevo.userid = id;
        nuevos.push_back(nuevo);
        return nuevos;
    }
    vector <Contacto> borrarContacto(int id){
        int contador = 0;
        vector <Contacto> nuevos = contactos;
        for(Contacto c:contactos){
            if(id == c.id){
                nuevos.erase(nuevos.begin()+contador);
            }else{
                contador++;
            }
        }
        return nuevos;
    }
    Contacto buscarContacto (int id){
        Contacto buscado;
        for(Contacto c:contactos){
            if(id==c.id){
                buscado = c;
            }
        }
        return buscado;
    }
    int contarContactos (){
        int x = 0;
        for(Contacto c:contactos){
            x++;
        }
        return x;
    }
};
//PROTOTIPO DE OPERADORES DE USUARIO
istream& operator>> (istream&,Usuario&);
ostream& operator<< (ostream&,Usuario&);
//EXCEPCIONES PROPIAS
class ExcepcionCaracteres{
public:
    ExcepcionCaracteres(){}
};
class ExcepcionNoTelefono{
public:
    ExcepcionNoTelefono(){}
};
class ExcepcionNoCorreo{
public:
    ExcepcionNoCorreo(){}
};
//PROTOTIPOS DE FUNCIONES
long long verificarNumero();
int leerInt();
vector <Usuario> leerUsuariosF();
Usuario registrarUsuario(vector<Usuario>);
void guardarUsuariosF(vector <Usuario>);
int main(){
    char decision;
    vector <Usuario> usuarios;
    try{
        do{
            usuarios = leerUsuariosF();
            cout << "PRODUCTO INTEGRADOR" << endl;
            cout << "(l)Iniciar sesion" << endl;
            cout << "(r)Registrarse" << endl;
            cout << "(p)Mostrar lista de usuarios" << endl;
            cout << "(s)Buscar usuario" << endl;
            cout << "(e)Salir" << endl;
            cin >> decision;
            switch(decision){
            case 'l':
                {

                }
                break;
            case 'r':
                {
                    cin.ignore();
                    usuarios.push_back(registrarUsuario(usuarios));
                    guardarUsuariosF(usuarios);
                }
                break;
            case 'p':
                {
                    for(Usuario u:usuarios){
                        cout << u << endl;
                    }
                }
                break;
            case 's':
                {
                    int idBuscado;
                    bool encontrado = false;
                    cout << "ID del usuario a buscar:";
                    idBuscado = leerInt();
                    for(Usuario u:usuarios){
                        if(u.getId() == idBuscado){
                            encontrado = true;
                            cout << u << endl;
                            break;
                        }
                    }
                    if(!encontrado){
                        cout << "Lo sentimos, no pudimos encontrar un usuario con ese ID" << endl;
                    }
                }
                break;
            }
        }while(decision != 'e');
    }catch(...){
        cout << "Error desconocido" << endl;
    }
}

int leerInt(){ //Valida le entrada
    int x;
    cin >> x;
        if(cin.peek() != '\n' && cin.peek() != ' '){
            cin.clear(ios::badbit);
        }
        if(cin.good())
            return x;
        //!si la entrada no fue correcta
        else if (cin.fail()){
            cin.clear(); // pone 0 a todos los indicadores de error
            cin.ignore(numeric_limits<int>::max(),'\n'); /*!numeric_limits<int>::max()
                                        retorna la maypr cant de digitos que almacena
                                        un dato int*/
            cout << "\nVuelve a intentarlo";
            return leerInt();
        }
}
long long leerNumero(){ //Se valida la entrada de numeros long long
    long long num;
    cin >> num;
    if(cin.peek() != '\n' && cin.peek() != ' '){
        cin.clear(ios::badbit);
    }
    if(cin.good()){
        return num;
    }
    else if(cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<int>::max(),'\n');
        cout << "Error al leer el numero, vuelve a intentar" << endl;
        return leerNumero();
    }
}
Usuario registrarUsuario(vector <Usuario> usuarios){ //Pide la entrada de un usuario para registrarlo en archivos
    Usuario usuario;
    cin >> usuario;

    int tam;
    int id;
    if(usuarios.empty()){
       usuario.setId(1);
    }else{
        tam = usuarios.size()-1;
        id = usuarios[tam].getId()+1;
        usuario.setId(id);
    }
    return usuario;
}
vector <Usuario> leerUsuariosF(){ //En esta función se buscan los archivos de usuarios y contactos para incluir todo en un vector de Usuarios*/
    vector <Usuario> usuarios;
    vector <Contacto> contactos;
    Usuario usuario;
    Contacto contacto;
    ifstream ifs ("usuarios.txt");
    ifstream ifs2 ("contactos.txt");
    string auxiliar = "";
    string auxiliar2 = "";
    string user = "";
    string pass = "";
    int id = 0;
    if(ifs.is_open() && ifs2.is_open()){
        while(!ifs.eof()){
            getline(ifs,auxiliar);
            if(!auxiliar.empty()){
                if(auxiliar.find("User ID:")!=string::npos){
                    id = stoi(auxiliar.substr(auxiliar.find("User ID:")+8));
                }
                if(auxiliar.find("Username:")!=string::npos){
                    user = auxiliar.substr(auxiliar.find("Username:")+9);
                }
                if(auxiliar.find("Password:")!=string::npos){
                    pass = auxiliar.substr(auxiliar.find("Password:")+9);
                }
                if(auxiliar.find("**********")!=string::npos){
                    while(!ifs2.eof()){
                        getline(ifs2,auxiliar2);
                        if(auxiliar2.find("UID:")!=string::npos){
                            contacto.userid = stoi(auxiliar2.substr(auxiliar2.find("UID:")+4));
                        }
                        if(auxiliar2.find("ID:")!=string::npos){
                            contacto.id = stoi(auxiliar2.substr(auxiliar2.find("ID:")+3));
                        }
                        if(auxiliar2.find("Nombre:")!=string::npos){
                            contacto.nombre = auxiliar2.substr(auxiliar2.find("Nombre:")+7);
                        }
                        if(auxiliar2.find("Celular:")!=string::npos){
                            contacto.celular = stoll(auxiliar2.substr(auxiliar2.find("Celular:")+8));
                        }
                        if(auxiliar2.find("Telefono de casa:")!=string::npos){
                            contacto.telefonoC = stoll(auxiliar2.substr(auxiliar2.find("Telefono de casa:")+17));
                        }
                        if(auxiliar2.find("Telefono de trabajo:")!=string::npos){
                            contacto.telefonoT = stoll(auxiliar2.substr(auxiliar2.find("Telefono de trabajo:")+20));
                        }
                        if(auxiliar2.find("Correo:")!=string::npos){
                            contacto.correo = auxiliar2.substr(auxiliar2.find("Correo:")+7);
                        }
                        if(auxiliar2.find("Direccion:")!=string::npos){
                            contacto.direccion = auxiliar2.substr(auxiliar2.find("Direccion:")+10);
                        }
                        if(auxiliar2.find("Descripcion:")!=string::npos){
                            contacto.descrip = auxiliar2.substr(auxiliar2.find("Descripcion:")+12);
                        }
                        if(auxiliar2.find("**********")!=string::npos && contacto.id == id){
                            contactos.push_back(contacto);
                        }
                    }
                    usuario.setId(id);
                    usuario.setUser(user);
                    usuario.setPass(pass);
                    usuario.setContactos(contactos);
                    usuarios.push_back(usuario);
                }
            }
        }
    }
    return usuarios;
}
void guardarUsuariosF(vector <Usuario> usuarios){
    ofstream ofs ("usuarios.txt");
    ofstream ofs2 ("contactos.txt");
    if(!usuarios.empty()){
        for(Usuario u:usuarios){
            ofs << "User ID:" << u.getId() << endl
            << "Username:" << u.getUser() << endl
            << "Password:" << u.getPass() << endl
            << "**********" << endl;
            for(Contacto c:u.getContactos()){
                ofs2 << "UID:" <<  u.getId() << endl
                << "ID:" << c.id << endl
                << "Nombre:" << c.nombre << endl
                << "Celular:" << c.celular << endl
                << "Telefono de casa:" << c.telefonoC << endl
                << "Telefono de trabajo:" << c.telefonoT << endl
                << "Correo:" << c.correo << endl
                << "Direccion:" << c.direccion << endl
                << "Descripcion:" << c.descrip << endl
                << "**********" << endl;
            }
        }
    }
}
istream& operator>> (istream& is, Contacto& contacto){ //Operador para ingresar Contacto
    bool entradaCorrecta = false;
    do{
        try{
            cout<<"Nombre:"<<endl;
            getline(is,contacto.nombre);
            if(contacto.nombre.length()>50 || contacto.nombre.length()<=0){
                throw ExcepcionCaracteres();
            }else{
                entradaCorrecta = true;
            }
        }catch(ExcepcionCaracteres e){
            cout << "El nombre es demasiado largo, o esta vacio (maximo 50 caracteres)" << endl;
        }
    }while(!entradaCorrecta);
    entradaCorrecta = false;
    do{
        try{
            cout << "Celular:"<<endl;
            contacto.celular=leerNumero();
            if(contacto.celular>8999999999 || contacto.celular<800000000){
                throw ExcepcionNoTelefono();
            }else{
                entradaCorrecta = true;
            }
        }catch(ExcepcionNoTelefono e){
            cout << "El numero que ingreso no es valido como numero telefonico" << endl;
        }
    }while(!entradaCorrecta);
        entradaCorrecta = false;
    do{
        try{
            cout << "Telefono de casa:"<<endl;
            contacto.telefonoC=leerNumero();
            if(contacto.telefonoC>8999999999 || contacto.telefonoC<800000000){
                throw ExcepcionNoTelefono();
            }else{
                entradaCorrecta = true;
            }
        }catch(ExcepcionNoTelefono e){
            cout << "El numero que ingreso no es valido como numero telefonico" << endl;
        }
    }while(!entradaCorrecta);
    entradaCorrecta = false;
    do{
        try{
            cout << "Telefono de trabajo:"<<endl;
            contacto.telefonoT=leerNumero();
            if(contacto.telefonoT>8999999999 || contacto.telefonoT<800000000){
                throw ExcepcionNoTelefono();
            }else{
                entradaCorrecta = true;
            }
        }catch(ExcepcionNoTelefono e){
            cout << "El numero que ingreso no es valido como numero telefonico" << endl;
        }
    }while(!entradaCorrecta);
    entradaCorrecta = false;
    do{
        try{
            cout<<"Correo:"<<endl;
            is.ignore();
            getline(is,contacto.correo);
            if(contacto.correo.length()>100 || contacto.correo.length()<=0){
                throw ExcepcionCaracteres();
            }else{
                if(contacto.correo.find("@") != string::npos && contacto.correo.find(".com") != string::npos){
                    entradaCorrecta = true;
                }else{
                    throw ExcepcionNoCorreo();
                }
            }
        }catch(ExcepcionCaracteres e){
            cout << "El correo es demasiado largo, o esta vacio (maximo 100 caracteres)" << endl;
        }catch(ExcepcionNoCorreo e){
            cout << "No se ingreso un correo valido" << endl;
        }
    }while(!entradaCorrecta);
    entradaCorrecta = false;
    do{
        try{
            cout<<"Direccion:"<<endl;
            getline(is,contacto.direccion);
            if(contacto.direccion.length()>130 || contacto.direccion.length()<=0){
                throw ExcepcionCaracteres();
            }else{
                entradaCorrecta = true;
            }
        }catch(ExcepcionCaracteres e){
            cout << "La direccion es demasiado larga, o esta vacia (maximo 130 caracteres)" << endl;
        }
    }while(!entradaCorrecta);
    entradaCorrecta = false;
    do{
        try{
            cout<<"Descripcion:"<<endl;
            getline(is,contacto.descrip);
            if(contacto.descrip.length()>100 || contacto.descrip.length()<=0){
                throw ExcepcionCaracteres();
            }else{
                entradaCorrecta = true;
            }
        }catch(ExcepcionCaracteres e){
            cout << "La descripcion es demasiado larga, o esta vacia (maximo 100 caracteres)" << endl;
        }
    }while(!entradaCorrecta);
    return is;
}
ostream& operator<< (ostream& os, Contacto& contacto){ //Operador para mostrar Contacto
    os <<"Nombre:"<<contacto.nombre<<endl
    <<"Celular:"<<contacto.celular<<endl
    <<"Telefono de casa:"<<contacto.telefonoC<<endl
    <<"Telefono de trabajo:"<<contacto.telefonoT<<endl
    <<"Correo:"<<contacto.correo<<endl
    <<"Direccion:"<<contacto.direccion<<endl
    <<"Descripcion:"<<contacto.descrip<<endl;
    return os;
}
istream& operator>> (istream& is, Usuario& usuario){ //Operador para ingresas Usuario
    bool entradaCorrecta = false;
    string u = "";
    string p = "";
    char d;
    vector <Contacto> c;
    do{
        try{
            cout << "Username:" <<endl;
            getline(is,u);
            if(u.length()>15 || u.length()<=0){
                throw ExcepcionCaracteres();
            }else{
                entradaCorrecta = true;
                usuario.setUser(u);
            }
        }catch(ExcepcionCaracteres e){
            cout << "El usuario es demasiado largo, o  esta vacio (Maximo 15 caracteres)" << endl;
        }
    }while(!entradaCorrecta);
    entradaCorrecta = false;
    do{
        try{
            cout << "Password:" <<endl;
            getline(is,p);
            if(u.length()<=0){
                throw ExcepcionCaracteres();
            }else{
                entradaCorrecta = true;
                usuario.setPass(p);
            }
        }catch(ExcepcionCaracteres e){
            cout << "El password esta vacio" << endl;
        }
    }while(!entradaCorrecta);
    cout << "Deseas agregar un contacto? (s)" << endl;
    is >> d;
    if(d == 's'){
        do{
            is.ignore();
            c = usuario.agregarContacto();
            usuario.setContactos(c);
            cout << "Deseas agregar otro contacto? (s/n)" << endl;
            is >> d;
        }while(d == 's');
    }
    return is;
}
ostream& operator<< (ostream& os, Usuario& usuario){ //Operador para mostrar Usuario
    os << "User ID:" << usuario.getId() << endl
    << "Username:" << usuario.getUser() << endl
    << "Contactos:"  << usuario.contarContactos() << endl;
    return os;
}
