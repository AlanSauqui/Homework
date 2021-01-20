#include <bits/stdc++.h>

using namespace std;

//Inicializacion del mapa de las keys
    map<string,pair<string,int> > keys = {
        { "entier", make_pair("Tipos de datos",100) },
        { "flottant", make_pair("Tipos de datos",100) },
        { "chaine", make_pair("Tipos de datos",100) },
        { "bool", make_pair("Tipos de datos",100) },
        { "if", make_pair("Instruccion",101) },
        { "else", make_pair("Instruccion",101) },
        { "alors", make_pair("Instruccion",101) },
        { "pour", make_pair("Instruccion",101) },
        { "lis", make_pair("Instruccion",101) },
        { "montrer", make_pair("Instruccion",101) },
        { "true", make_pair("Valor booleano",203) },
        { "false", make_pair("Valor booleano",203) },
        { "==", make_pair("Operadores relacionales",301) },
        { "<=", make_pair("Operadores relacionales",301) },
        { ">=", make_pair("Operadores relacionales",301) },
        { "!=", make_pair("Operadores relacionales",301) }
    };

//Mapa de simbolos
    map<string,pair<string,string> > tablaSimbolos;

//Lectura de datos
    string leerArchivo();




//---------------------------Analizador Lexico Codigo----------------------------------------

//Funciones Analizador Lexico
    vector<pair<string,int> > analizadorLexico(string);
    void checkKey(string, vector<pair<string,int> > &);
    bool isInt(string);
    bool isFloat(string);
    bool simbol(char);

//Funcion principal del Analizador Lexico
vector<pair<string,int> > analizadorLexico(string s){
    vector<pair<string,int> > al;
    string str;
    for(int i=0;i<s.size();i++){
        if( isalpha(s[i]) != 0 && str.size() == 0 ){ //Checa si el primer simbolo de una "palabra" es una letra del abecedario
            str += s[i];
            if( isalnum(s[i+1]) == 0 ){
                checkKey(str, al);
                str = "";
            }
        }
        else if( isalnum(s[i]) == 0 && s[i] != ' ' && s[i] != '\n'  && s[i] != '.' && s[i] != 9){ //Checa si el primer simbolo de una "palabra" no es alfanumurico
            if( ( (int(s[i]) >= 60 && int(s[i]) <= 62) || s[i] == '!') && (s[i+1] == '=') ){ //Checa si es un operador relacional
                str += s[i];
                str += s[i+1];
                checkKey(str, al);
                str = "";
                i++;
            }
            else if( int(s[i]) == 39 ){ //Checa si es una expresion entre "comillas" ('expresion')
                str += s[i];
                pair<string,int> p = make_pair(str,303);
                al.emplace_back(p);
                str = "";

                i++;
                while( int(s[i]) != 39 && s[i] != '\n' && s[i] != '\0' ){
                    str += s[i];
                    i++;
                }
                p = make_pair(str,202);
                al.emplace_back(p);
                str = "";

                if(int(s[i]) != 39){
                    cout << endl << "ERROR. EL STRING NO TIENE FINAL"  << endl << endl;
                    exit(EXIT_FAILURE);
                }
                str += s[i];
                p = make_pair(str,303);
                al.emplace_back(p);

                str = "";
            }
            else{ //Checa si es un simbolo independiente
                str += s[i];
                pair<string,int> p;
                if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%'){ //Operadores aritmeticos
                    p = make_pair(str,300);
                    al.emplace_back(p);
                }
                else if(s[i] == '>' || s[i] == '<'){ //Operadores relacionales
                    p = make_pair(str,301);
                    al.emplace_back(p);
                }
                else if(s[i] == '&' || s[i] == '|' || s[i] == '!'){ //Operadores logicos
                    p = make_pair(str,302);
                    al.emplace_back(p);
                }
                else if(s[i] == ';' || s[i] == '(' || s[i] == ')' || s[i] == '{' || s[i] == '}' || s[i] == '='){ //Simbolos
                    p = make_pair(str,303);
                    al.emplace_back(p);
                }
                else{
                    cout << endl << "ERROR. ELEMENTO NO VALIDO DENTRO DEL CODIGO" << " ----> (" << s[i] << ")" << endl << endl;
                    exit(EXIT_FAILURE);
                }
                str = "";
            }
        }
        else if( isalnum(s[i]) != 0 && str.size() > 0 ){ //Checa si despues de una letra del abecedario continua un simbolo alfanumurico
            str += s[i];
            if( isalnum(s[i+1]) == 0 ){
                checkKey(str, al);
                str = "";
            }
        }
        else if((isdigit(s[i]) || s[i]=='.') && !simbol(s[i]) && !isalpha(s[i])){
            while(s[i] != ' ' && i<s.size() && !simbol(s[i]) && !isalpha(s[i])){
                str = str + s[i];
                i++;
            }
            if(isInt(str) && !str.empty()){
                pair<string,int> p = make_pair(str,200);
                al.emplace_back(p);
                str = "";
                //llamar a funcion para guardar entero
                //cout<<"Int: "<<numint<<endl;
            }
            else if (isFloat(str)){
                pair<string,int> p = make_pair(str,201);
                al.emplace_back(p);
                str = "";
                //cout<<"Float: "<<numfloat<<endl;
            }
            else if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n'){
                cout << endl << "ERROR. ELEMENTO DESCONOCIDO INTRODUCIDO"  << " ----> (" << str << ")" << endl << endl;
                exit(EXIT_FAILURE);
            }
            str = "";
            i--;
        }
    }
    return al;
}

//Checa el string o token y determina mediante el map que es
void checkKey(string str, vector<pair<string,int> > &al){
    if( keys.find(str) != keys.end() ){
        pair<string,int> p = make_pair(str,keys[str].second);
        al.emplace_back(p);
    }
    else if( isalpha(str[0]) != 0 ){
        pair<string,int> p = make_pair(str,102);
        al.emplace_back(p);
    }
}

//Determina si el numero es entero
bool isInt(string num){
    for(int i=0;i<num.size();i++){
        if(num[i] == '.') return false;
    }
    return true;
}

//Determina si el numero es flotante
bool isFloat(string num){
    int cont = 0;
    for(int i=0;i<num.size();i++){
        if(num[i] == '.') cont++;
    }
    if(cont == 1) return true;
    else return false;
}

//Determina simbolos que puedan interferir con la construccion de un numero
bool simbol(char c){
    if(((int)c > 0 && (int)c <=45) || ((int)c>= 58 && (int)c <= 64 ) ||  ((int)c >= 91 && (int)c <= 96) || (int)c >= 123 || (int)c == 47) return true;
    else return false;
}

//-------------------------------------------------------------------------------------------





//------------------------------Analizador Sintactico---------------------------------------

class Expresion
{
    private:
        queue<pair<string,int> > lista_tokens;
        string expresionResumida;
        string funcionPadre;
        bool esEntero;
        bool esFloat;
        bool esCadena;
        bool esExpresionBooleana;
        bool esExpresionCadena;
        bool tieneEntero;
        bool tieneFlotante;
    public:
        Expresion(){

        }
        Expresion(queue<pair<string,int> > _lista_tokens){
            this->lista_tokens = _lista_tokens;
            this->expresionResumida = "";
            this->funcionPadre = "";
            this->esEntero = false;
            this->esCadena = false;
            this->esFloat = false;
            this->esExpresionBooleana = false;
            this->esExpresionCadena = false;
            this->tieneEntero = false;
            this->tieneFlotante = false;
        }
        ~Expresion(){

        }

    //-----------------------------------------Evaluacion----------------------------------------

    void print(stack<string> s){
        while(!s.empty()){
            cout<<s.top()<<endl;
            s.pop();
        }
        cout<<endl;
    }

    void printfl(stack<float> s){
    cout<<endl<<"stack"<<endl;
        while(!s.empty()){
            cout<<s.top()<<endl;
            s.pop();
        }
        cout<<endl;
    }

    void printq(queue<pair<string,int>> s){
        while(!s.empty()){
            cout<<s.front().first<<",";
            s.pop();
        }
        cout<<endl;
    }
    void printq(queue<string> s){
        while(!s.empty()){
            cout<<s.front();
            s.pop();
        }
        cout<<endl;
    }

    queue<pair<string,int> > reviewTokens(queue<pair<string,int> > tokens){
        queue<pair<string,int> > tokensR;
        stack<pair<string,int> > op;
        while(!tokens.empty()){
            if((isInt(tokens.front().first) || isFloat(tokens.front().first) || tokens.front().first.compare("%")==0 || tokens.front().first.compare("*")==0 || tokens.front().first.compare("/")==0 || tokens.front().second==301 || tokens.front().second==302 || tokens.front().second==303) && op.empty()){
                tokensR.push(tokens.front());
                tokens.pop();
            }
            else if(tokens.front().first.compare("+")==0 || tokens.front().first.compare("-")==0){
                if(op.empty()){
                    op.push(make_pair(tokens.front().first,tokens.front().second));
                    tokens.pop();
                    //print(op);
                }
                else{
                    if((op.top().first.compare("+")==0 && tokens.front().first.compare("+")==0) || (op.top().first.compare("-")==0 && tokens.front().first.compare("-")==0)){
                        op.pop();
                        op.push(make_pair("+",300));
                        //print(op);
                    }
                    else{
                        if(op.top().first.compare("+")==0){
                            op.pop();
                            op.push(make_pair("-",300));
                        }
                        else{
                            op.pop();
                            op.push(make_pair("+",300));
                        }
                        //print(op);
                    }
                    tokens.pop();
                }
            }
            else if(!op.empty()){
                if(tokensR.empty()){
                    if(op.top().first.compare("-")==0){
                        string s = "-"+tokens.front().first;
                        tokensR.push(make_pair(s,tokens.front().second));
                        tokens.pop();
                        op.pop();
                    }
                    else{
                        op.pop();
                        tokensR.push(tokens.front());
                        tokens.pop();
                    }
                }
                else if(tokensR.back().first.compare("*")==0 || tokensR.back().first.compare("/")==0 || tokensR.back().first.compare("(")==0 || tokensR.back().first.compare("%")==0){
                    if(op.top().first.compare("-")==0){
                        string s = "-"+tokens.front().first;
                        tokensR.push(make_pair(s,tokens.front().second));
                        tokens.pop();
                        op.pop();
                    }
                    else{
                        op.pop();
                        tokensR.push(tokens.front());
                        tokens.pop();
                    }
                }
                else{
                    tokensR.push(op.top());
                    op.pop();
                }
                //printq(tokensR);
            }
        }
        //printq(tokensR);
        return tokensR;
    }

    float evaluate(queue<pair<string,int> > tokens){
        queue<string> q;
        stack<string> op;
        tokens = reviewTokens(tokens);
        while(!tokens.empty()){
            pair<string,int> p = tokens.front();
            //cout<<p.first<<endl;
            tokens.pop();
            if(isInt(p.first) || isFloat(p.first)){
                q.push(p.first);
            }
            else{
                if(op.empty() || p.first.compare("(")==0 ){
                    op.push(p.first);
                    //print(op);
                }
                else if(p.first.compare(")")==0){
                    while(!op.empty() && op.top().compare("(")!=0){
                        q.push(op.top());
                        op.pop();
                        //print(op);
                    }
                    op.pop();
                    //print(op);
                }
                else{
                    if(p.first.compare("!")==0){ //error raro con el signo de not !
                        while(!op.empty() && (priority(op.top()) > priority(p.first))){
                            q.push(op.top());
                            op.pop();
                        }
                    op.push(p.first);
                    //print(op);
                    }
                    else{
                        while(!op.empty() && (priority(op.top()) >= priority(p.first))){
                        q.push(op.top());
                        op.pop();
                    }
                    op.push(p.first);
                    //print(op);
                    }
                }
            }
            //printq(tokens);
        }
        while(!op.empty()){
            q.push(op.top());
            op.pop();
        }
        //printq(q);

        stack<float> numbers;
        while(!q.empty()){
            if(isInt(q.front()) || isFloat(q.front())){
                float aux = stof(q.front(),nullptr);
                numbers.push(aux);
            }
            else{
                if(q.front().compare("!")==0){
                    //printfl(numbers);
                    float aux = numbers.top();
                    numbers.pop();
                    numbers.push(notOperation(aux));
                }
                else{
                    //printfl(numbers);
                    float first = numbers.top();
                    numbers.pop();
                    float second = numbers.top();
                    numbers.pop();
                    numbers.push(operation(first,q.front(),second));
                }
            }
            q.pop();
        }
        //cout<<"res "<<numbers.top()<<endl;
        return numbers.top();
    }

    float notOperation(float a){
        if(a == 0) {
            //cout<<a<<" entro"<<endl;
            return 1;
        }
        else if(a==1) {
            return 0;
        }
        return 0;
    }

    float operation(float b, string op, float a){
        if(op.compare("+")==0){
            //cout<<a<<"+"<<b<<"="<<a+b<<endl;
            return a+b;
        }
        if(op.compare("-")==0){
            //cout<<a<<"-"<<b<<"="<<a-b<<endl;
            return a-b;
        }
        if(op.compare("/")==0){
            //cout<<a<<"/"<<b<<"="<<a/b<<endl;
            return a/b;
        }
        if(op.compare("*")==0){
            //cout<<a<<"*"<<b<<"="<<a*b<<endl;
            return a*b;
        }
        if(op.compare("<=")==0){
            //cout<<a<<"<="<<b<<"="<<(a<=b)<<endl;
            return a<=b;
        }
        if(op.compare(">=")==0){
            //cout<<a<<">="<<b<<"="<<(a>=b)<<endl;
            return a>=b;
        }
        if(op.compare("==")==0){
            //cout<<a<<"=="<<b<<"="<<(a==b)<<endl;
            return a==b;
        }
        if(op.compare("!=")==0){
            //cout<<a<<"!="<<b<<"="<<(a!=b)<<endl;
            return a!=b;
        }
        if(op.compare(">")==0){
            //cout<<a<<">"<<b<<"="<<(a>b)<<endl;
            return a>b;
        }
        if(op.compare("<")==0){
            //cout<<a<<"<"<<b<<"="<<(a<b)<<endl;
            return a<b;
        }
        /*if(op.compare("!")==0){
            return a!b;
        }*/
        if(op.compare("|")==0){
            //cout<<a<<"|"<<b<<"="<<(a||b)<<endl;
            return a||b;
        }
        if(op.compare("&")==0){
            //cout<<a<<"&"<<b<<"="<<(a&&b)<<endl;
            return a&&b;
        }
        if(op.compare("%")==0){
            //cout<<a<<"%"<<b<<"="<<(a%b)<<endl;
            return int(a)%int(b);
        }
        return 0;
    }

    int priority(string op){
        if(op.compare("*")==0 || op.compare("/")==0) return 6;
        else if(op.compare("%")==0) return 5;
        else if(op.compare("-")==0 || op.compare("+")==0) return 4;
        else if(op.compare(">=")==0 || op.compare("<=")==0 || op.compare("<")==0 || op.compare(">")==0 || op.compare("==")==0 || op.compare("!=")==0) return 3;
        else if(op.compare("!")==0) return 2;
        else if(op.compare("|")==0) return 1;
        else if(op.compare("&")==0) return 0;
        else return -1;
    }

    bool isInt(string num){
        for(int i=0;i<num.size();i++){
            if(num[i]=='-') i++;
            if(num[i] == '.' || !isdigit(num[i])) return false;
        }
        return true;
    }

    bool isFloat(string num){
        int cont = 0;
        for(int i=0;i<num.size();i++){
            if(num[i] == '.') cont++;
        }
        if(cont == 1) return true;
        else return false;
    }

//-------------------------------------------------------------------------------------------

        void imprimirError(string texto){
            cout << endl << texto << endl << endl;
            exit(EXIT_FAILURE);
        }
        bool isChain(queue<pair<string,int> > lista1){
            if(lista1.size() > 1){
                // cout <<this->lista_tokens.front().first << "    "<< this->lista_tokens.front().second << endl;
                return false;
            }
            if(lista1.front().second != 202 && lista1.front().second != 102){
                // cout << lista1.front().first << "    "<< lista1.front().second << endl;
                return false;
            }
            if( tablaSimbolos.find(lista1.front().first) != tablaSimbolos.end() ){
                if( tablaSimbolos[lista1.front().first].first != "chaine" ){
                    return false;
                }
                // cout << tablaSimbolos[lista1.front().first].second << endl;
                // cout <<lista1.front().first << "    "<< lista1.front().second << endl;
                // return false;
            }
            // cout << tablaSimbolos[lista1.front().first].first << "    "<< lista1.front().first << endl;
            return true;
        }
        bool isBoolExpression(queue<pair<string,int> > lista1){
            // cout <<lista1.front().first << "    "<< lista1.front().second << endl;
            while (!lista1.empty()){
                if(lista1.front().second != 102 && lista1.front().second != 300 && lista1.front().second != 301 && lista1.front().second != 302 && lista1.front().second != 200 && lista1.front().second != 201 && lista1.front().second != 203 && int(lista1.front().first[0]) != 40 && int(lista1.front().first[0]) != 41){
                    // cout <<lista1.front().first << "    "<< lista1.front().second << endl;
                    return false;
                }
                if( tablaSimbolos.find(lista1.front().first) != tablaSimbolos.end() ){
                    if( tablaSimbolos[lista1.front().first].first == "chaine" ){
                        return false;
                    }
                }
                if( lista1.front().second == 201 ){
                    this->tieneFlotante = true;
                    this->tieneEntero = false;
                }
                else if( (lista1.front().second == 200 || lista1.front().second == 203) && this->tieneFlotante == false ){
                    this->tieneEntero = true;
                }
                else if( lista1.front().second == 102 ){
                    if( this->isFloat(lista1.front().first) == true ){
                        this->tieneFlotante = true;
                        this->tieneEntero = false;
                    }
                    else if( this->isInt(lista1.front().first) == true && this->tieneFlotante == false ){
                        this->tieneEntero = true;
                    }
                }
                lista1.pop();
            }
            return true;
        }
        void revisarExpresion(queue<pair<string,int> > &lista){
            // cout <<lista.front().first << "    "<< lista.front().second << endl;
            if(this->isChain(this->lista_tokens) == false && this->isBoolExpression(lista) == false){
                this->imprimirError("ERROR. LO QUE SE ESPERABA DE EXPRESION NO CORRESPONDE CON LO QUE SE INTRODUJO PARA " + this->funcionPadre);
            }
            if(this->isChain(this->lista_tokens) == true){
                this->esExpresionCadena = true;
                // cout << "Hlaa" << endl;
                this->expresionResumida = lista.front().first;
                return;
            }
            if(this->isBoolExpression(lista) == true){
                this->esExpresionBooleana = true;
                this->expresionResumida = to_string(this->evaluate(lista));
                return;
            }
        }
        queue<pair<string,int> > sustituir(queue<pair<string,int> > lista){ //Sustituye el valor en la variable
            queue<pair<string,int> > lista1;
            while (!lista.empty()){
                if( tablaSimbolos.find(lista.front().first) != tablaSimbolos.end() ){
                    lista1.push(make_pair(tablaSimbolos[lista.front().first].second, lista.front().second));
                }
                else if( tablaSimbolos.find(lista.front().first) == tablaSimbolos.end() && lista.front().second == 102 ){
                    this->imprimirError("ERROR. VARIABLE DESCONOCIDA ---> "+lista.front().first);
                }
                else if(lista.front().second == 203){
                    if(lista.front().first == "true"){
                        lista1.push(make_pair("1", lista.front().second));
                    }
                    else{
                        lista1.push(make_pair("0", lista.front().second));
                    }
                }
                else{
                    lista1.push(make_pair(lista.front().first, lista.front().second));
                }
                lista.pop();
            }
            return lista1;
        }
        void evaluar(){
            queue<pair<string,int> > lista = this->sustituir(this->lista_tokens);
            this->revisarExpresion(lista);
            if( this->funcionPadre == "MONTRER" ){

            }
            else if( (this->esEntero == true || this->esFloat == true) && this->esExpresionBooleana == false ){
                this->imprimirError("ERROR. LO QUE SE ESPERABA DE EXPRESION NO CORRESPONDE CON LO QUE SE INTRODUJO PARA " + this->funcionPadre + ", SE ESPERABA UN EXPRESION BOOLEANA");
            }
            else if( this->esCadena == true && this->esExpresionCadena == false ){
                this->imprimirError("ERROR. LO QUE SE ESPERABA DE EXPRESION NO CORRESPONDE CON LO QUE SE INTRODUJO PARA " + this->funcionPadre + ", SE ESPERABA UNA CADENA");
            }
        }
        string getExpresion(){
            return this->expresionResumida;
        }
        bool getIsBoolExpresion(){
            return this->esExpresionBooleana;
        }
        bool getIsChainExpresion(){
            return this->esExpresionCadena;
        }
        bool getTieneEntero(){
            return this->tieneEntero;
        }
        bool getTieneFlotante(){
            return this->tieneFlotante;
        }
        void setFuncionPadre(string x){
            this->funcionPadre = x;
        }
        void setEsEntero(bool x){
            this->esEntero = x;
        }
        void setEsFloat(bool x){
            this->esFloat = x;
        }
        void setEsCadena(bool x){
            this->esCadena = x;
        }
        void setEsExpresionBooleana(bool x){
            this->esExpresionBooleana = x;
        }
        void setEsExpresionCadena(bool x){
            this->esExpresionCadena = x;
        }
        void imprimirR(queue<pair<string,int> > lista){
            if(lista.empty() == false){
                cout << "\" ";
                while (!lista.empty()){
                    cout << lista.front().first << " ";
                    lista.pop();
                }
                cout << "\"";
            }
            else{
                cout << "Expresion vacia" << endl;
            }
        }
        void imprimir(){
            imprimirR(this->lista_tokens);
        }
};

class Instruccion
{
    public:
        Instruccion(){

        }
        ~Instruccion(){

        }
        virtual void ejecutar(){

        }
        virtual void imprimir(){

        }
        virtual void setEspacios(int){

        }
        virtual void imprimirEspacios(){

        }
};

class Declarar : public Instruccion
{
    private:
        string nombre_variable;
        string tipo_variable;
        int espacios;
    public:
        Declarar(){

        }
        Declarar(string _nombre_variable, string _tipo_variable){
            this->espacios = 0;
            this->nombre_variable = _nombre_variable;
            this->tipo_variable  = _tipo_variable;
        }
        ~Declarar(){

        }
        void ejecutar(){
            if(this->tipo_variable == "entier"){
                string cero = "0";
                tablaSimbolos[this->nombre_variable] = make_pair(this->tipo_variable, cero);
            }
            else if(this->tipo_variable == "flottant"){
                string cero = "0.0";
                tablaSimbolos[this->nombre_variable] = make_pair(this->tipo_variable, cero);
            }
            else if(this->tipo_variable == "bool"){
                string cero = "0";
                tablaSimbolos[this->nombre_variable] = make_pair(this->tipo_variable, cero);
            }
            else if(this->tipo_variable == "chaine"){
                tablaSimbolos[this->nombre_variable] = make_pair(this->tipo_variable, "");
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "DECLARAR---> ";
            cout << "Nombre: " << this->nombre_variable << ",   Tipo: " << this->tipo_variable << endl;
        }
};

class Asignar : public Instruccion
{
    private:
        string nombre_variable;
        Expresion *expresion;
        int espacios;
    public:
        Asignar(){

        }
        Asignar(string _nombre_variable, Expresion *_expresion){
            this->espacios = 0;
            this->nombre_variable = _nombre_variable;
            this->expresion = _expresion;
        }
        ~Asignar(){
            delete this->expresion;
        }
        void ejecutar(){
            if( tablaSimbolos.find(this->nombre_variable) == tablaSimbolos.end() ){
                // cout << this->nombre_variable << endl;
                cout << "ERROR. NO EXISTE ESTA VARIABLE" << endl;
                exit(EXIT_FAILURE);
            }
            this->expresion->setFuncionPadre(nombre_variable);
            if(tablaSimbolos[this->nombre_variable].first == "entier"){
                this->expresion->setEsEntero(true);
                this->expresion->evaluar();
                int entero = stoi(this->expresion->getExpresion());
                tablaSimbolos[this->nombre_variable].second = to_string(entero);
            }
            else if(tablaSimbolos[this->nombre_variable].first == "flottant"){
                this->expresion->setEsFloat(true);
                this->expresion->evaluar();
                tablaSimbolos[this->nombre_variable].second = this->expresion->getExpresion();
            }
            else if(tablaSimbolos[this->nombre_variable].first == "chaine"){
                this->expresion->setEsCadena(true);
                this->expresion->evaluar();
                tablaSimbolos[this->nombre_variable].second = this->expresion->getExpresion();
            }
            else if(tablaSimbolos[this->nombre_variable].first == "bool"){
                this->expresion->setEsEntero(true);
                this->expresion->evaluar();
                int booleano = stof(this->expresion->getExpresion());
                if(booleano > 0 || booleano < 0){
                    string si = "1";
                    tablaSimbolos[this->nombre_variable].second = si;
                }
                else{
                    string no = "0";
                    tablaSimbolos[this->nombre_variable].second = no;
                }
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "ASIGNAR---> ";
            cout << "Nombre: " << this->nombre_variable << ",   Expresion: ";
            this->expresion->imprimir();
            cout << endl;
        }
};

class Montrer : public Instruccion //Imprimir
{
    private:
        Expresion *expresion;
        int espacios;
    public:
        Montrer(){

        }
        Montrer(Expresion *_expresion){
            this->espacios = 0;
            this->expresion = _expresion;
        }
        ~Montrer(){
            delete this->expresion;
        }
        void ejecutar(){
            this->expresion->setFuncionPadre("MONTRER");
            this->expresion->setEsCadena(true);
            this->expresion->setEsEntero(true);
            this->expresion->setEsFloat(true);
            this->expresion->evaluar();

            if( this->expresion->getIsBoolExpresion() == true ){
                string str = "";
                if( this->expresion->getTieneEntero() == true ){
                    int entero = stoi(this->expresion->getExpresion());
                    cout << entero << endl;
                }
                else if( this->expresion->getTieneFlotante() == true ){
                    cout << this->expresion->getExpresion() << endl;
                }
            }
            else if( this->expresion->getIsChainExpresion() == true ){
                cout << this->expresion->getExpresion() << endl;
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "Montrer---> Expresion: ";
            this->expresion->imprimir();
            cout << endl;
        }
};

class Lis : public Instruccion //Leer
{
    private:
        string nombre_variable;
        int espacios;
    public:
        Lis(){

        }
        Lis(string _nombre_variable){
            this->espacios = 0;
            this->nombre_variable = _nombre_variable;
        }
        ~Lis(){

        }
        void imprimirError(string texto){
            cout << endl << texto << endl << endl;
            exit(EXIT_FAILURE);
        }
        bool esNumero(string &str){
            bool flag = true;
            for(int i=0;i<str.length();i++){
                if( str[0] == '-' ){
                    flag &= true;
                }
                else if(isdigit(str[i]) != 0 || int(str[i]) == 46){
                    flag &= true;
                }
                else{
                    flag &= false;
                }
            }
            return flag;
        }
        bool isInt(string num){
            for(int i=0;i<num.size();i++){
                if(num[i] == '.') return false;
            }
            return true;
        }
        bool isFloat(string num){
            int cont = 0;
            for(int i=0;i<num.size();i++){
                if(num[i] == '.') cont++;
            }
            if(cont == 1) return true;
            else return false;
        }
        void ejecutar(){
            if( tablaSimbolos.find(this->nombre_variable) == tablaSimbolos.end() ){
                cout << "ERROR. NO EXISTE ESTA VARIABLE" << endl;
                exit(EXIT_FAILURE);
            }
            string x = "";
            if(tablaSimbolos[this->nombre_variable].first == "entier"){
                cin >> x;
                if(esNumero(x) == false){
                    this->imprimirError("ERROR. LA VARIABLE ES ENTIER Y HA RECIBIDO ALGO DIFERENTE ENTIER");
                }
                if(isFloat(x) == false && isInt(x) == false){
                    this->imprimirError("ERROR. LA VARIABLE ES ENTIER Y HA RECIBIDO ALGO DIFERENTE ENTIER");
                }
                int entero = stoi(x);
                tablaSimbolos[this->nombre_variable].second = to_string(entero);
            }
            else if(tablaSimbolos[this->nombre_variable].first == "flottant"){
                cin >> x;
                if(this->esNumero(x) == false){
                    this->imprimirError("ERROR. LA VARIABLE ES FLOTTANT Y HA RECIBIDO ALGO DIFERENTE FLOTTANT");
                }
                if(this->isFloat(x) == false){
                    this->imprimirError("ERROR. LA VARIABLE ES FLOTTANT Y HA RECIBIDO ALGO DIFERENTE FLOTTANT");
                }
                tablaSimbolos[this->nombre_variable].second = x;
            }
            else if(tablaSimbolos[this->nombre_variable].first == "chaine"){
                cin >> x;
                tablaSimbolos[this->nombre_variable].second = x;
            }
            else if(tablaSimbolos[this->nombre_variable].first == "bool"){
                cin >> x;
                if(esNumero(x) == true){
                    if(esNumero(x) == false){
                        this->imprimirError("ERROR. LA VARIABLE ES BOOL Y HA RECIBIDO ALGO DIFERENTE BOOL");
                    }
                    if(isFloat(x) == false && isInt(x) == false){
                        this->imprimirError("ERROR. LA VARIABLE ES BOOL Y HA RECIBIDO ALGO DIFERENTE BOOL");
                    }
                    int booleano = stof(x);
                    if(booleano > 0 || booleano < 0){
                        string si = "1";
                        tablaSimbolos[this->nombre_variable].second = si;
                    }
                    else{
                        string no = "0";
                        tablaSimbolos[this->nombre_variable].second = no;
                    }

                }
                else if(x == "true"){
                    string si = "1";
                    tablaSimbolos[this->nombre_variable].second = si;
                }
                else if(x == "false"){
                    string no = "0";
                    tablaSimbolos[this->nombre_variable].second = no;
                }
                else{
                    this->imprimirError("ERROR. LA VARIABLE ES BOOL Y HA RECIBIDO ALGO DIFERENTE BOOL");
                }
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "Lis---> Nombre: " << this->nombre_variable << endl;
        }
};

class If : public Instruccion
{
    private:
        Expresion *expresion;
        queue<Instruccion*> lista_si;
        queue<Instruccion*> lista_sino;
        int espacios;
    public:
        If(){

        }
        If(Expresion *_expresion, queue<Instruccion*> _lista_si){
            this->espacios = 0;
            this->expresion = _expresion;
            this->lista_si = _lista_si;
        }
        If(Expresion *_expresion, queue<Instruccion*> _lista_si, queue<Instruccion*> _lista_sino){
            this->espacios = 0;
            this->expresion = _expresion;
            this->lista_si = _lista_si;
            this->lista_sino = _lista_sino;
        }
        ~If(){
            while(!this->lista_si.empty()){
                delete this->lista_si.front();
                this->lista_si.pop();
            }
            while(!this->lista_sino.empty()){
                delete this->lista_sino.front();
                this->lista_sino.pop();
            }
        }
        void hacerInstrucciones(queue<Instruccion*> lista1){
            while (!lista1.empty()){
                lista1.front()->ejecutar();
                lista1.pop();
            }
        }
        void ejecutar(){
            this->expresion->setFuncionPadre("IF");
            this->expresion->setEsEntero(true);
            this->expresion->evaluar();
            int x = stoi(this->expresion->getExpresion());
            // cout << this->expresion->getExpresion() << "  holaaa" << endl;
            // cout << x << endl;
            if(x > 0 || x < 0){
                this->hacerInstrucciones(this->lista_si);
            }
            else{
                if(this->lista_sino.empty() == false){
                    this->hacerInstrucciones(this->lista_sino);
                }
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimirInstrucciones(queue<Instruccion*> lista1){
            while (!lista1.empty()){
                lista1.front()->setEspacios(this->espacios+1);
                lista1.front()->imprimir();
                lista1.pop();
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "IF---> Expresion: ";
            this->expresion->imprimir();
            cout << endl;
            this->imprimirEspacios();
            cout << "Instrucciones if:" << endl;
            if(this->lista_si.empty() == false){
                this->imprimirInstrucciones(this->lista_si);
            }
            if(this->lista_sino.empty() == false){
                this->imprimirEspacios();
                cout << "Instrucciones else:" << endl;
                this->imprimirInstrucciones(this->lista_sino);
            }
        }
};

class Pour : public Instruccion //For
{
    private:
        string nombre_variable;
        int valor_inicio;
        int valor_fin;
        int incremento;
        queue<Instruccion*> lista;
        int espacios;
    public:
        Pour(){

        }
        Pour(string _nombre_variable, int _valor_inicio, int _valor_fin, int _incremento, queue<Instruccion*> _lista){
            this->espacios = 0;
            this->nombre_variable = _nombre_variable;
            this->valor_inicio = _valor_inicio;
            this->valor_fin = _valor_fin;
            this->incremento = _incremento;
            this->lista = _lista;
        }
        ~Pour(){
            while(!this->lista.empty()){
                delete this->lista.front();
                this->lista.pop();
            }
        }
        void hacerInstrucciones(queue<Instruccion*> lista1){
            while (!lista1.empty()){
                lista1.front()->ejecutar();
                lista1.pop();
            }
        }
        void ejecutar(){
            if( tablaSimbolos.find(this->nombre_variable) == tablaSimbolos.end() ){
                cout << "ERROR. NO EXISTE ESTA VARIABLE PARA EL POUR" << endl;
                exit(EXIT_FAILURE);
            }
            if( tablaSimbolos[this->nombre_variable].first != "entier" && tablaSimbolos[this->nombre_variable].first != "float" ){
                cout << "ERROR. LA VARIABLE CONTADORA DEL POUR NO ES PERMITIDO" << endl;
                exit(EXIT_FAILURE);
            }
            tablaSimbolos[this->nombre_variable].second = to_string(this->valor_inicio);
            for(stoi(tablaSimbolos[this->nombre_variable].second); stoi(tablaSimbolos[this->nombre_variable].second) <= this->valor_fin; tablaSimbolos[this->nombre_variable].second = to_string(stoi(tablaSimbolos[this->nombre_variable].second)+this->incremento) ){
                hacerInstrucciones(this->lista);
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimirInstrucciones(queue<Instruccion*> lista1){
            while (!lista1.empty()){
                lista1.front()->setEspacios(this->espacios+1);
                lista1.front()->imprimir();
                lista1.pop();
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "POUR---> NombreVar: " << this->nombre_variable << ",   ValorInicio: " << to_string(this->valor_inicio) << ",   ValorFin: " << to_string(this->valor_fin) << ",   Incremento: " << to_string(this->incremento) << endl;
            this->imprimirEspacios();
            cout << "Instrucciones pour:" << endl;
            if(this->lista.empty() == true){
                this->imprimirEspacios();
                cout << "     No hay instrucciones" << endl;
                return;
            }
            this->imprimirInstrucciones(this->lista);
        }
};

class Alors : public Instruccion //While
{
    private:
        Expresion *expresion;
        queue<Instruccion*> lista;
        int espacios;
    public:
        Alors(){

        }
        Alors(Expresion *_expresion, queue<Instruccion*> _lista){
            this->espacios = 0;
            this->expresion = _expresion;
            this->lista = _lista;
        }
        ~Alors(){
            delete this->expresion;
            while(!this->lista.empty()){
                delete this->lista.front();
                this->lista.pop();
            }
        }
        void hacerInstrucciones(queue<Instruccion*> lista1){
            while (!lista1.empty()){
                lista1.front()->ejecutar();
                lista1.pop();
            }
        }
        void ejecutar(){
            this->expresion->setFuncionPadre("ALORS");
            this->expresion->setEsEntero(true);
            this->expresion->evaluar();
            int x = stoi(this->expresion->getExpresion());
            while (x > 0 || x < 0){
                hacerInstrucciones(this->lista);
                this->expresion->evaluar();
                x = stoi(this->expresion->getExpresion());
            }
        }
        void setEspacios(int data){
            this->espacios = data;
        }
        void imprimirEspacios(){
            if(this->espacios > 0){
                for(int i=0;i<espacios;i++){
                    cout << "     ";
                }
            }
        }
        void imprimirInstrucciones(queue<Instruccion*> lista1){
            while (!lista1.empty()){
                lista1.front()->setEspacios(this->espacios+1);
                lista1.front()->imprimir();
                lista1.pop();
            }
        }
        void imprimir(){
            this->imprimirEspacios();
            cout << "ALORS---> Expresion: ";
            this->expresion->imprimir();
            cout << endl;
            this->imprimirEspacios();
            cout << "Instrucciones alors:" << endl;
            if(this->lista.empty() == true){
                this->imprimirEspacios();
                cout << "     No hay instrucciones" << endl;
                return;
            }
            this->imprimirInstrucciones(this->lista);
        }
};

//Variables globales
    int iGlobal = 0;
    int contInst = 0;
    int contExpre = 0;
    Instruccion *instrucciones[1000];
    Expresion *expresiones[1000];
    bool avisoRecursion = false;
//Funciones Analizador Sintactico
    queue<Instruccion*> analizadorSintactico(vector<pair<string,int> >&, int, string);
    void revisarContador(int, int, string);
    void revisarVaciadoPairs(queue<pair<string,int> >&, string);
    void revisarVaciadoInstrucciones(queue<Instruccion*>&, string);
    bool checarParentesis(int, int, vector<pair<string,int> >&);
    void ifGeneral(queue<Instruccion*>&, vector<pair<string,int> >&, int&);
    void ifVerif(vector<pair<string,int> >&, queue<pair<string,int> >&, int&);
    void elseVerif(vector<pair<string,int> >&);
    void alorsVerif(queue<Instruccion*>&, vector<pair<string,int> >&, int&);
    void pourVerif(queue<Instruccion*>&, vector<pair<string,int> >&, int&);
    void lisVerif(queue<Instruccion*>&, vector<pair<string,int> >&);
    void montrerVerif(queue<Instruccion*> &, vector<pair<string,int> >&);
    void asignarVerif(queue<Instruccion*> &,vector<pair<string,int> >&);


//Funciones secundarias del Analizador Sintáctico desglosadas

void revisarContador(int i, int tamano, string texto){
    if(i>=tamano){
        cout << endl << texto << endl << endl;
        exit(EXIT_FAILURE);
    }
}

void revisarVaciadoPairs(queue<pair<string,int> > &expresionG, string texto){
    if(expresionG.empty() == true){
        cout << endl << texto << endl << endl;
        exit(EXIT_FAILURE);
    }
}

void revisarVaciadoInstrucciones(queue<Instruccion*> &instruccionesG, string texto){
    if(instruccionesG.empty() == true){
        cout << endl << texto << endl << endl;
        exit(EXIT_FAILURE);
    }
}

bool checarParentesis(int i, int cambiante,vector<pair<string,int> > &al){ //Checar paréntesis y que haya un corchete de apertura
    if(i>=al.size()){ //Verificar si no esta vacio el siguiente elemento y no de error
        return false;
    }
    if(int(al[i].first[0]) != 40){
        return false;
    }
    i++;
    if(i>=al.size()){ //Verificar si no esta vacio el siguiente elemento y no de error
        return false;
    }
    while(i<al.size()-1){
        if(int(al[i].first[0]) == 41 && int(al[i+1].first[0]) == cambiante){
            return true;
        }
        i++;
        if(i>=al.size()-1){
            break;
        }
    }
    return false;
}

void ifGeneral(queue<Instruccion*> &listaInstrucciones, vector<pair<string,int> > &al, int &nivel){
    iGlobal++;
    queue<pair<string,int> > expresionIf;
    int indiceExpresion = 0;
    ifVerif(al, expresionIf, indiceExpresion);
    queue<Instruccion*> listaInstruccionesIf = analizadorSintactico(al, nivel+1, "IF"); //Reitera el proceso para lo que esta dentro de ese if
    revisarVaciadoInstrucciones(listaInstruccionesIf, "ERROR. LA FUNCION IF NO CONTIENE INSTRUCCIONES, ESTA VACIA");
    iGlobal++;
    if(iGlobal<al.size()){ //Verificar si no esta vacio el siguiente elemento y no de error
        if(al[iGlobal].first == "else"){
            iGlobal++;
            elseVerif(al); //Mandar a repetir lo mismo que en el if
            iGlobal++;
            revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION ELSE NO CONTIENE INSTRUCCIONES"); //Verificar si no esta vacio el siguiente elemento y no de error
            queue<Instruccion*> listaInstruccionesElse = analizadorSintactico(al, nivel+1, "ELSE");
            revisarVaciadoInstrucciones(listaInstruccionesElse, "ERROR. LA FUNCION ELSE NO CONTIENE INSTRUCCIONES, ESTA VACIA");
            instrucciones[contInst] = new If(expresiones[indiceExpresion],listaInstruccionesIf,listaInstruccionesElse);
            listaInstrucciones.push(instrucciones[contInst]);
            contInst++;
            contExpre++;
        }
        else{
            instrucciones[contInst] = new If(expresiones[indiceExpresion],listaInstruccionesIf);
            listaInstrucciones.push(instrucciones[contInst]);
            contInst++;
            contExpre++;
            iGlobal--;
        }
    }
    else if( iGlobal >= al.size() ){
        instrucciones[contInst] = new If(expresiones[indiceExpresion],listaInstruccionesIf);
        listaInstrucciones.push(instrucciones[contInst]);
        contInst++;
        contExpre++;
    }
}

void ifVerif(vector<pair<string,int> > &al, queue<pair<string,int> > &expresionIf, int &indiceExpresion){
    if(checarParentesis(iGlobal, 123, al) == false){ //Revisa si están los dos parentesis
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION IF, NO SE HIZO USO DE PARENTESIS"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    while(int(al[iGlobal].first[0]) != 123 && iGlobal < al.size()-1){ //Va juntando los tokens para la expresion
        if(al[iGlobal].second != 300 && al[iGlobal].second != 301 && al[iGlobal].second != 302 && al[iGlobal].second != 102 && al[iGlobal].second != 200 && al[iGlobal].second != 201 && al[iGlobal].second != 203 && int(al[iGlobal].first[0]) != 40 && int(al[iGlobal].first[0]) != 41){
            cout << endl << "ERROR. LA FUNCION IF CONTIENE UNA EXPRESION NO PERMITIDA"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        if(int(al[iGlobal].first[0]) == 41 && int(al[iGlobal+1].first[0]) == 123){
            iGlobal++;
            break;
        }
        expresionIf.push(make_pair(al[iGlobal].first,al[iGlobal].second));
        iGlobal++;
    }
    revisarVaciadoPairs(expresionIf, "ERROR. LA FUNCION IF NO CONTIENE UNA EXPRESION");
    expresiones[contExpre] = new Expresion(expresionIf);
    indiceExpresion = contExpre;
    iGlobal++;
    contExpre++;
    revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION IF NO CONTIENE INSTRUCCIONES"); //Verificar si no esta vacio el siguiente elemento y no de error
}

void elseVerif(vector<pair<string,int> > &al){
    revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION ELSE NO CONTIENE INSTRUCCIONES"); //Verificar si no esta vacio el siguiente elemento y no de error
    if(int(al[iGlobal].first[0]) != 123){ //Verificar si esta el "{"
        cout << endl << "ERROR. LA FUNCION ELSE NO CONTIENE CORCHETE DE ABRIR"  << endl << endl;
        exit(EXIT_FAILURE);
    }
}

void alorsVerif(queue<Instruccion*> &listaInstrucciones, vector<pair<string,int> > &al, int &nivel){
    iGlobal++;
    if(checarParentesis(iGlobal, 123, al) == false){ //Revisa si están los dos parentesis y el corchete de apertura "{"
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION ALORS, NO SE HIZO USO DE PARENTESIS"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    queue<pair<string,int> > expresionAlors;
    while(int(al[iGlobal].first[0]) != 123 && iGlobal < al.size()-1){ //Va juntando los tokens para la expresion
        if(int(al[iGlobal].first[0]) == 41 && int(al[iGlobal+1].first[0]) == 123){
            iGlobal++;
            break;
        }
        if(al[iGlobal].second != 300 && al[iGlobal].second != 301 && al[iGlobal].second != 302 && al[iGlobal].second != 102 && al[iGlobal].second != 200 && al[iGlobal].second != 201 && al[iGlobal].second != 203 && int(al[iGlobal].first[0]) != 40 && int(al[iGlobal].first[0]) != 41){
            cout << endl << "ERROR. LA FUNCION ALORS CONTIENE UNA EXPRESION NO PERMITIDA"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        expresionAlors.push(make_pair(al[iGlobal].first,al[iGlobal].second));
        iGlobal++;
    }
    revisarVaciadoPairs(expresionAlors, "ERROR. LA FUNCION ALORS NO CONTIENE UNA EXPRESION");
    expresiones[contExpre] = new Expresion(expresionAlors);
    int indiceExpresion = contExpre;
    revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION ALORS NO CONTIENE INSTRUCCIONES"); //Verificar si no esta vacio el siguiente elemento y no de error
    if(int(al[iGlobal].first[0]) != 123){ //Verificar si esta el "{"
        cout << endl << "ERROR. LA FUNCION ALORS NO CONTIENE CORCHETE DE ABRIR"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    contExpre++;
    queue<Instruccion*> listaInstruccionesAlors = analizadorSintactico(al, nivel+1, "ALORS");
    revisarVaciadoInstrucciones(listaInstruccionesAlors, "ERROR. LA FUNCION ALORS NO CONTIENE INSTRUCCIONES, ESTA VACIA");
    instrucciones[contInst] = new Alors(expresiones[indiceExpresion],listaInstruccionesAlors);
    listaInstrucciones.push(instrucciones[contInst]);
    contInst++;
}

void pourVerif(queue<Instruccion*> &listaInstrucciones, vector<pair<string,int> > &al, int &nivel){
    iGlobal++; //pour(i;0;100;1)
    if(checarParentesis(iGlobal, 123, al) == false){ //Revisa si están los dos parentesis
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO SE HIZO USO DE PARENTESIS"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    if(al[iGlobal].second != 102){ //(i)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO CONTIENE VARIABLE A UTILIZAR DE CONTADOR"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    int indiceVar = iGlobal;
    iGlobal++;
    if(int(al[iGlobal].first[0]) != 59){ //(i;)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO CONTIENE PUNTO Y COMA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    if(al[iGlobal].second != 200){ //(i;0)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NUMERO INCICIAL"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    int varInicial = stoi(al[iGlobal].first);
    iGlobal++;
    if(int(al[iGlobal].first[0]) != 59){ //(i;0;)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO CONTIENE PUNTO Y COMA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    if(al[iGlobal].second != 200){ //(i;0;10)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO CONTIENE NUMERO FINAL"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    int varFinal = stoi(al[iGlobal].first);
    iGlobal++;
    if(int(al[iGlobal].first[0]) != 59){ //(i;0;10;)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO CONTIENE PUNTO Y COMA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    if(al[iGlobal].second != 200){ //(i;0;10;1)
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION POUR, NO CONTIENE INCREMENTO"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    int varIncremento = stoi(al[iGlobal].first);
    iGlobal += 3;
    revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION POUR NO CONTIENE INSTRUCCIONES"); //Verificar si no esta vacio el siguiente elemento y no de error
    queue<Instruccion*> listaInstruccionesPour = analizadorSintactico(al, nivel+1, "POUR");
    revisarVaciadoInstrucciones(listaInstruccionesPour, "ERROR. LA FUNCION POUR NO CONTIENE INSTRUCCIONES, ESTA VACIA");
    instrucciones[contInst] = new Pour(al[indiceVar].first, varInicial, varFinal, varIncremento, listaInstruccionesPour);
    listaInstrucciones.push(instrucciones[contInst]);
    contInst++;
}

void lisVerif(queue<Instruccion*> &listaInstrucciones, vector<pair<string,int> > &al){
    iGlobal++;
    // cout << "LIS ----> "<< al[iGlobal].first << endl;
    if(al.size()-1-iGlobal < 3){ //Declarar
        cout << endl << "ERROR. LA INSTRUCCION LIS SE HA ESCRITO DE MANERA INCORRECTA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    if(int(al[iGlobal].first[0]) == 40 && al[iGlobal+1].second == 102 && int(al[iGlobal+2].first[0]) == 41 && int(al[iGlobal+3].first[0]) == 59){
        instrucciones[contInst] = new Lis(al[iGlobal+1].first);
        listaInstrucciones.push(instrucciones[contInst]);
        contInst++;
        iGlobal += 3;
        // cout << "holsssss" << endl;
    }
    else{
        cout << endl << "ERROR. LA INSTRUCCION LIS SE HA ESCRITO DE MANERA INCORRECTA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
}

void montrerVerif(queue<Instruccion*> &listaInstrucciones, vector<pair<string,int> > &al){
    iGlobal++;
    queue<pair<string,int> > expresionMontrer;
    if(checarParentesis(iGlobal, 59, al) == false){ //Revisa si están los dos parentesis y el punto y coma
        cout << endl << "ERROR. USO INCORRECTO DE LA INSTRUCCION MONTRER, NO SE HIZO USO DE PARENTESIS"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;
    if(int(al[iGlobal].first[0]) == 39){
        iGlobal++;
        revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION MONTRER NO CONTIENE EXPRESION"); //Verificar si no esta vacio el siguiente elemento y no de error
        if(al[iGlobal].second != 202){
            cout << endl << "ERROR. LA FUNCION MONTRER TIENE UNA COMBINACION DE EXPRESION INCORRECTA, SE ESPERABA UN STRING"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        expresionMontrer.push(make_pair(al[iGlobal].first,al[iGlobal].second));
        iGlobal++;
        revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION MONTRER QUE ES UN STRING, NO CONTIENE LA COMILLA FINAL"); //Verificar si no esta vacio el siguiente elemento y no de error
        if(int(al[iGlobal].first[0]) != 39){ //Checar si está la comilla de cierre
            cout << endl << "ERROR. LA FUNCION MONTRER QUE ES UN STRING, NO CONTIENE LA COMILLA FINAL"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        iGlobal++;
        revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION MONTRER QUE ES UN STRING, NO CONTIENE EL PARENTESIS FINAL"); //Verificar si no esta vacio el siguiente elemento y no de error
        if(int(al[iGlobal].first[0]) != 41){ //Checar si está la comilla de cierre
            cout << endl << "ERROR. LA FUNCION MONTRER QUE ES UN STRING, NO CONTIENE EL PARENTESIS FINAL"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        iGlobal++;
    }
    else{
        while(int(al[iGlobal].first[0]) != 59 && iGlobal < al.size()){ //Va juntando los tokens para la expresion
            if(al[iGlobal].second != 300 && al[iGlobal].second != 301 && al[iGlobal].second != 302 && al[iGlobal].second != 102 && int(al[iGlobal].first[0]) != 40 && int(al[iGlobal].first[0]) != 41 && al[iGlobal].second != 200 && al[iGlobal].second != 201 && al[iGlobal].second != 203){
                cout << endl << "ERROR. LA FUNCION MONTRER CONTIENE UNA EXPRESION NO PERMITIDA"  << endl << endl;
                exit(EXIT_FAILURE);
            }

            if(int(al[iGlobal].first[0]) == 41 && int(al[iGlobal+1].first[0]) == 59){
                iGlobal++;
                break;
            }

            expresionMontrer.push(make_pair(al[iGlobal].first,al[iGlobal].second));
            iGlobal++;
        }
    }
    revisarContador(iGlobal,al.size(),"ERROR. LA FUNCION MONTRER NO CONTIENE PUNTO Y COMA"); //Verificar si no esta vacio el siguiente elemento y no de error
    if(int(al[iGlobal].first[0]) != 59){
        cout << endl << "ERROR. LA FUNCION MONTRER NO CONTIENE PUNTO Y COMA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    expresiones[contExpre] = new Expresion(expresionMontrer);
    instrucciones[contInst] = new Montrer(expresiones[contExpre]);
    listaInstrucciones.push(instrucciones[contInst]);
    contInst++;
    contExpre++;
}

void asignarVerif(queue<Instruccion*> &listaInstrucciones, vector<pair<string,int> > &al){
    int indiceVar = iGlobal;
    iGlobal++;
    queue<pair<string,int> > expresionAsignar;
    revisarContador(iGlobal,al.size(),"ERROR. LA ASIGNACION DE VARIABLE NO ESTA BIEN ESTRUCTURADA"); //Verificar si no esta vacio el siguiente elemento y no de error
    if(int(al[iGlobal].first[0]) != 61){
        cout << endl << "ERROR. LA ASIGNACION DE VARIABLE NO ESTA BIEN ESTRUCTURADA"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    iGlobal++;

    revisarContador(iGlobal,al.size(),"ERROR. LA ASIGNACION DE VARIABLE NO CONTIENE EXPRESION"); //Verificar si no esta vacio el siguiente elemento y no de error
    if(int(al[iGlobal].first[0]) == 39){
        iGlobal++;
        revisarContador(iGlobal,al.size(),"ERROR. LA ASIGNACION DE VARIABLE NO CONTIENE EXPRESION"); //Verificar si no esta vacio el siguiente elemento y no de error
        if(al[iGlobal].second != 202){
            cout << endl << "ERROR. LA ASIGNACION DE VARIABLE TIENE UNA COMBINACION DE EXPRESION INCORRECTA, SE ESPERABA UN STRING"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        int indiceExpresion = iGlobal;
        iGlobal++;
        revisarContador(iGlobal,al.size(),"ERROR. LA ASIGNACION DE VARIABLE, QUE ES UN STRING, NO CONTIENE LA COMILLA FINAL"); //Verificar si no esta vacio el siguiente elemento y no de error
        if(int(al[iGlobal].first[0]) != 39){
            cout << endl << "ERROR. LA ASIGNACION DE VARIABLE, QUE ES UN STRING, NO CONTIENE LA COMILLA FINAL"  << endl << endl;
            exit(EXIT_FAILURE);
        }
        expresionAsignar.push(make_pair(al[indiceExpresion].first, al[indiceExpresion].second));
        iGlobal++;
    }
    else{
        while(int(al[iGlobal].first[0]) != 59 && iGlobal < al.size()){ //Va juntando los tokens para la expresion
            if(al[iGlobal].second != 300 && al[iGlobal].second != 301 && al[iGlobal].second != 302 && al[iGlobal].second != 102 && int(al[iGlobal].first[0]) != 40 && int(al[iGlobal].first[0]) != 41 && al[iGlobal].second != 200 && al[iGlobal].second != 201 && al[iGlobal].second != 203){
                cout << endl << "ERROR. LA ASIGNACION DE VARIABLE CONTIENE UNA EXPRESION NO PERMITIDA"  << endl << endl;
                exit(EXIT_FAILURE);
            }
            expresionAsignar.push(make_pair(al[iGlobal].first,al[iGlobal].second));
            iGlobal++;
            if(iGlobal >= al.size() && int(al[iGlobal-1].first[0]) != 59){
                cout << endl << "ERROR. LA ASIGNACION DE VARIABLE CONTIENE UNA EXPRESION NO PERMITIDA"  << endl << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    revisarContador(iGlobal,al.size(),"ERROR. LA ASIGNACION DE VARIABLE NO CONTIENE EL PUNTO Y COMA FINAL"); //Verificar si no esta vacio el siguiente elemento y no de error
    if(int(al[iGlobal].first[0]) != 59){
        cout << endl << "ERROR. LA ASIGNACION DE VARIABLE NO CONTIENE EL PUNTO Y COMA FINAL"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    expresiones[contExpre] = new Expresion(expresionAsignar);
    instrucciones[contInst] = new Asignar(al[indiceVar].first, expresiones[contExpre]);
    listaInstrucciones.push(instrucciones[contInst]);
    contInst++;
    contExpre++;
}

//Funcion principal del Analizador Sintáctico
queue<Instruccion*> analizadorSintactico(vector<pair<string,int> > &al, int nivel, string funcionIterativa){
    if(al.size() == 0){
        cout << endl << "ERROR. NO HAY NINGUN TOKEN"  << endl << endl;
        exit(EXIT_FAILURE);
    }
    queue<Instruccion*> listaInstrucciones;
    for(iGlobal;iGlobal<al.size();iGlobal++){
        if(iGlobal < al.size()){ //Checa corchete final
            if(al[iGlobal].first == "else"){
                cout << endl << "ERROR. SE HA INTRODUCIDO ELSE DE MANERA INCORRECTA"  << endl << endl;
                exit(EXIT_FAILURE);
            }
            if(int(al[iGlobal].first[0]) == 125 && nivel == 0){ //Checa que el corchete de cierre no sea parte de una funcion recursiva, para detectar corchetes de mas
                cout << endl << "ERROR. SE HA INTRODUCIDO UN CORCHETE DE MAS"  << endl << endl;
                exit(EXIT_FAILURE);
            }
            if(int(al[iGlobal].first[0]) == 125 && nivel > 0){ //Retorna la lista a la funcion recursiva
                return listaInstrucciones;
            }
        }

        if(al[iGlobal].second == 100 && al.size()-1-iGlobal >= 2){ //Declarar
            if(al[iGlobal].first == "entier"){ //Entero
                if(al[iGlobal+1].second == 102 && int(al[iGlobal+2].first[0]) == 59){
                    instrucciones[contInst] = new Declarar(al[iGlobal+1].first,"entier");
                    listaInstrucciones.push(instrucciones[contInst]);
                    contInst++;
                }
                else{
                    cout << endl << "ERROR. DECLARACION ERRONEA PARA ENTIER"  << endl << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(al[iGlobal].first == "flottant"){ //Flotante
                if(al[iGlobal+1].second == 102 && int(al[iGlobal+2].first[0]) == 59){
                    instrucciones[contInst] = new Declarar(al[iGlobal+1].first,"flottant");
                    listaInstrucciones.push(instrucciones[contInst]);
                    contInst++;
                }
                else{
                    cout << endl << "ERROR. DECLARACION ERRONEA PARA FLOTTANT"  << endl << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(al[iGlobal].first == "chaine"){ //Cadena
                if(al[iGlobal+1].second == 102 && int(al[iGlobal+2].first[0]) == 59){
                    instrucciones[contInst] = new Declarar(al[iGlobal+1].first,"chaine");
                    listaInstrucciones.push(instrucciones[contInst]);
                    contInst++;
                }
                else{
                    cout << endl << "ERROR. DECLARACION ERRONEA PARA CHAINE"  << endl << endl;
                    exit(EXIT_FAILURE);
                }
            }
            else if(al[iGlobal].first == "bool"){ //Booleano
                if(al[iGlobal+1].second == 102 && int(al[iGlobal+2].first[0]) == 59){
                    instrucciones[contInst] = new Declarar(al[iGlobal+1].first,"bool");
                    listaInstrucciones.push(instrucciones[contInst]);
                }
                else{
                    cout << endl << "ERROR. DECLARACION ERRONEA PARA BOOL"  << endl << endl;
                    exit(EXIT_FAILURE);
                }
            }
            iGlobal += 2;
        }

        else if(al[iGlobal].second == 101){ //Instrucciones
            if(al[iGlobal].first == "if"){ //if
                ifGeneral(listaInstrucciones, al, nivel);
            }
            else if(al[iGlobal].first == "lis"){ //Leer
                lisVerif(listaInstrucciones, al);
            }
            else if(al[iGlobal].first == "montrer"){ //Imprimir
                montrerVerif(listaInstrucciones, al);
            }
            else if(al[iGlobal].first == "alors"){ //while
                alorsVerif(listaInstrucciones, al, nivel);
            }
            else if(al[iGlobal].first == "pour"){
                pourVerif(listaInstrucciones, al, nivel);
            }
        }

        else if(al[iGlobal].second == 102){ //Asignaciones a variables
            asignarVerif(listaInstrucciones, al);
        }

        else if(al[iGlobal].second != 100 && al[iGlobal].second != 101 && al[iGlobal].second != 102 && int(al[iGlobal].first[0]) != 125){
            // cout << al[iGlobal-2].first << endl;
            // cout << al[iGlobal-1].first << endl;
            // cout << al[iGlobal].first << endl;
            cout << endl << "ERROR. SE HA INTRODUCIDO UNA INSTRUCCION ERRONEA"  << endl << endl;
            exit(EXIT_FAILURE);
        }

        if(iGlobal < al.size()){
            if(iGlobal+1 >= al.size() && int(al[iGlobal].first[0]) != 125 && nivel > 0){ //Checa el error de que una funcion recursiva no contenga un corchete de cierre
                cout << endl << "ERROR. UN " << funcionIterativa << " NO HA CONCLUIDO DE MANERA ADECUADA, LE HACE FALTA UN CORCHETE DE CIERRE "  << endl << endl;
                exit(EXIT_FAILURE);
            }
        }

    }

    return listaInstrucciones;
}


//-------------------------------------------------------------------------------------------






//------------------------------Analizador Semantico---------------------------------------
//Funciones del Analizador Semantico
    void analizadorSemantico(queue<Instruccion*>&);

//Funciones principal del Analizador Semantico
    void analizadorSemantico(queue<Instruccion*> &listaInstrucciones){
        cout << "Analizador Semantico: " << endl;
        while (!listaInstrucciones.empty()){
            listaInstrucciones.front()->ejecutar();
            listaInstrucciones.pop();
        }
        cout << endl << endl << endl;
    }


//-------------------------------------------------------------------------------------------







//---------------------------Lectura de datos------------------------------------------------

void esComentario(string &aux){
    if( aux.length() == 0 ){
        return;
    }
    for(int i=0;i<aux.length()-1;i++){
        if( int(aux[i]) == 47 && int(aux[i+1]) == 47 ){
            aux.erase(aux.begin()+i,aux.end());
            return;
        }
    }
}

string leerArchivo(){
    string s,nom,aux;
    ifstream archivo;

    cout<<"Nombre archivo: ";
    cin >> nom;
    archivo.open(nom,ios::in);

    if(archivo.fail()){
        cout<<"El archivo no se pudo abrir."<<endl;
        return 0;
    }

    while(!archivo.eof()){
        getline(archivo,aux);
        esComentario(aux);
        if( aux.length() > 0 ){
            aux += char(10);
            // cout << s << endl;
            s = s + aux;
        }
    }

    archivo.close();

    return s;
}

//-------------------------------------------------------------------------------------------





//--------------------------------Main------------------------------------------------------

//Funciones del Main
    void mostrarString(string&);
    void mostrarLexico(vector<pair<string,int> > &);
    void mostrarSintactico(queue<Instruccion*>);

//Funciones del Main desglosadas
    void mostrarString(string &s){
        cout << "String del codigo a emular: " << endl;
        cout << s << endl << endl << endl;
    }

    void mostrarLexico(vector<pair<string,int> > &al){
        cout << "Analizador Lexico: " << endl;
        for(auto x:al){
            cout << x.second << " : " << x.first << endl;
        }
        cout << endl << endl << endl;
    }

    void mostrarSintactico(queue<Instruccion*> listaInstrucciones){
        cout << "Analizador Sintactico: " << endl;
        while (!listaInstrucciones.empty()){
            listaInstrucciones.front()->imprimir();
            listaInstrucciones.pop();
        }
        cout << endl << endl << endl;
    }

//Main
int main(){
    string s = leerArchivo();
    mostrarString(s);
    vector<pair<string,int> > al = analizadorLexico(s);
    mostrarLexico(al);
    queue<Instruccion*> listaInstrucciones = analizadorSintactico(al,0,"Funcion principal");
    mostrarSintactico(listaInstrucciones);
    analizadorSemantico(listaInstrucciones);
    cout << endl << "Integrantes:" << endl << "-Josue Olmos Hernandez" << endl <<"-Alan Samuel Aguirre Salazar" << endl << endl;

    return 0;
}
//------------------------------------------------------------------------------------------
