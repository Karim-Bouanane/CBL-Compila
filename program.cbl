

Libraries :
com: tester la déclaration des bibliothèque; 
    lib : name,name2; 
    h : header1,header2; 
 

Constants :  
com: tester tous les types de variables;
    x = 4; 
    y = 0.5F;
    z = "Hello";
    w = 0.4D;
    c = 'a';
    ll = 410L;
    constfichier = FILE("C:/users/hp/dektop/fie.txt",'r'); 


Variables :  
com: tester tous les types de variables;  
    i = 4; 
    f = 0.5F;
    s = "Hello";
    d = 0.4D;
    r = 'a';
    l = 410L;
    varfichier, a; 
 

Functions : 
com: tester les fonctions;  
    function1(){
        return x; 
    } 

    function2(a,b){ 
        a = a + b;
        return a; 
    } 

    function3(a,b){
        a = 5;
        b = 6;
    }


Main():

com: test des opérateurs arithmétiques;
    i = i + 4;
    i = i - 4;
    i = i / 4;
    i = i % 4;
    i = i * 4;
    i = i ^ 4;

com: test des opérateurs de comparaison;
    i = i == 4;
    i = i != 4;
    i = i <= 4;
    i = i < 4;
    i = i >= 4;
    i = i >4;

com: test des opérateurs logique;
    i = i & 4;
    i = i | 4;

com: test de la condition if() elif() else;
    if ( i == 4){
        x = x + x;
    }elif( i > 4){
        x = (x - x)%a;
    }
    else {
    	return 4;
    }

com: test des boucles while() et do while();
    while( i == 0){
    	a = function2(i,b);
    }

    do {

    }while(i !=4);

com: test de la boucle for i in (1,n) ;
    for i in (1, 10){

    }
    for j in (1, x){
    	function3(j, x);
    }

com: test d'appel de fonctions;
    t = function1(); 
    t = function2(y, x); 