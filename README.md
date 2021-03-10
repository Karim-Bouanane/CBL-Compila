# **CBL-Compiler (CHOMK Blocs Lazy)**

## **Remerciements**

C’est avec un grand plaisir que nous réservons ces quelques lignes en signe de gratitude et de profonde reconnaissance à tous ceux qui, de près ou de loin, ont contribué à la réalisation et l’aboutissement de ce travail.

On saisit l’occasion pour remercier tous nos enseignants à l’ENSIAS qu’on offert des formations très complètes ce qui nous a aidé a bien aboutir notre projet, et bien précisément notre cours Compilation. Nous tenons également à exprimer notre sincère gratitude envers tous ceux qui nous ont aidé ou ont participé au bon déroulement de ce projet.

Enfin, nous exprimons nos plus vifs remerciements à notre enseignant et encadrant M.Younes TABII, pour ses précieux conseils et ses encouragements au cours de la préparation de ce projet.

</br>

## **Description**

Ce présent projet représente notre travail qui est  la réalisation d’un compilateur pour le langage propre de l’ENSIAS où nous avons travaillé avec le langage C et sans l’utilisation des générateurs de l’analyseur lexicale comme FLEX ou les générateurs de l’analyseur syntaxique comme BISON.

Afin d’appliquer les méthodologies et les notions enseignées durant le cours compilation, nous sommes invités à réaliser un projet qui nous permet d’appliquer nos connaissances théoriques sur le champ pratique.

Il s’agit d’un compilateur programmé avec le langage c. Le présent rapport est dédié à la présentation de l’ensemble des travaux menés dans le cadre de notre projet. La première partie est destinée à la présentation du grammaire LL(1) et au lexique. La deuxième partie aborde la réalisation de l’analyseur lexical. La troisième partie est destinée à la réalisation de l’analyseur syntaxique. Enfin, la conclusion générale résume le bilan du travail effectué et les principales perspectives.

</br>

### **Plan de cette documentation**
1.	Grammaire
2.  Tokens et symboles
3.	Documentation
	1. Analyseur Lexicale
	2. Analyseur Syntaxique
4.	Fonctionnement du Compilateur
5.	Future Amélioration
6.	Conclusion

</br>

# **1. Grammaire**

Terminaux  | Règles
------- | -------
**Prog** |  Lib { Const \| Var \| Func } Main
**Lib** | Libraries : \| [ lib: ID{,ID}; ] \| [ h: ID{,ID}; ] \| e 
**Const** | Constants : { ID = Value; } \| e 
**Var** | Variables : { ID [= Value] \| e ; } \| e 
**Func** | Functions : [ { ID ( { ID \| ID,} ) { Insts \| Return } } ] \| e 
**Main** | Main ( {ID \| ID,} ) { Insts } 
**Value** | int \| long \| float \| double \| string \| char \| List \| File \| 
**Int** | Num { Num } 
**Long** | Num { Num } L 
**Float** | Num { Num } [, Num { Num }] \| e F 
**Double** | Num { Num } [, Num { Num }] \| e D 
**String** | “ { Alpha \| Num \| Special }  ” 
**Char**  | ‘Alpha’ 
**List** | List < { ID \| value \| ID, \|value , \| } >
**File** | FILE ( string , ‘AccessType’); 
**AccessType** | r \| w 
**Insts** | Inst { Inst \| Return }  
**Inst** | CallFunction ; \| Decision \| Loop \| Affectation 
**Affectation** | ID { [num] } = { expr \| value} ;
**CallFunction** | ID ( { ID \| ID, } ) 
**Condition** | (expr Comp_Op expr) {logic_op (expr com_op expr)}  
**Decision** |  if ( condition ) { Insts } {elif { Insts } } { else {insts}}
**Loop** | for ID in Value { Insts } \| for ID in (Num, Num) { Insts } \| while (condition ){ Insts } \|  do{ Ints }while (condition);
**Expr** | TERM { [+|-] TERM } \| value
**TERM** | FACT { [ * \| / \| ^ \| % ]  FACT }
**FACT** | ID{ [num] } \| NUM \| (EXPR) \| CallFunction 
**Return** | return expr ; 
**Operator**  | Comp_Op \| Arith_Op \| Assign_Op \| Logic_Op 
**Comp_Op** | == \| < \| <= \| > \| >= \| != 
**Arith_Op** | + \| - \| /  \| *  \| ^ \| %  
**Assign_Op** | = 
**Logic_Op** | & \| \| 
**ID**  |  _ \| lettre { _ \| lettre \| chiffre} 
**Alpha** | a \| .. \| z \| A \| .. \| Z 
**Num** | 0 \| .. \| 9 
**Special** | Tous les caractères spéciaux 

</br>

# **2. Tokens et symboles** 

## **Program Structure Tokens**

Nom      | Symbol
---------|-------
LIBRARIES_TOKEN | Libraries 
CONST_TOKEN | Constants 
VAR_TOKEN | Variables 
FUNC_TOKEN | Functions 
MAIN_TOKEN | Main

</br>

## **Data Type Tokens**

Nom      | Symbol
---------|-------
INT_TOKEN | Int 
FLOAT_TOKEN | Float 
STRING_TOKEN | String 
DOUBLE_TOKEN | Double 
CHAR_TOKEN | Char 
LONG_TOKEN | Long 
LIST_TOKEN | List 
FILE_TOKEN | File 

</br>

## **Arithmetic operator Tokens**

Nom | Symbol
----|-------
PLUS_TOKEN | + 
MOINS_TOKEN | - 
DIV_TOKEN | / 
MOD_TOKEN | % 
MULT_TOKEN | * 
POWER_TOKEN | ^ 
EG_TOKEN | == 
DIFF_TOKEN | != 
INFEG_TOKEN | <= 
INF_TOKEN | < 
SUPEG_TOKEN | >= 
SUP_TOKEN | > 
AFF_TOKEN | = 

</br>

## **Logic operator Tokens**
Nom | Symbol
----|-------
AND_TOKEN | & 
OR_TOKEN | \|

</br>

## **Special Symbol Tokens**
Nom | Symbol
----|-------
BO_TOKEN | [ 
BF_TOKEN | ] 
PO_TOKEN | ( 
PF_TOKEN | ) 
PV_TOKEN | ; 
DP_TOKEN | : 
VIR_TOKEN | , 
CBO_TOKEN | { 
CBF_TOKEN | } 
ST_TOKEN | ‘’ 

</br>

## **Condition Tokens**
Nom | Symbol
----|-------
IF_TOKEN | if
ELIF_TOKEN | elif 
ELSE_TOKEN | else

</br>

## **Loop Tokens**
Nom | Symbol
----|-------
WHILE_TOKEN | while 
DO_TOKEN | do 
FOR_TOKEN | for 
IN_TOKEN | in 

</br>

## **Other Tokens**
Nom | Symbol
----|-------
ID_TOKEN
NUM_TOKEN
EOF_TOKEN
VARIABLE_TOKEN | variable 
LIB_TOKEN | Lib  
H_TOKEN | H 
RETURN_TOKEN | return

</br>

# **3. Documentation** 

## **2.1. Analyseur Lexicale**


```c
/*	Fonction 	: NextChar
	Description : Lit le prochain charactère et le retourne.
*/
char NextChar();

/*	Fonction 	: SaveToken
	Description : Enregistre dans un fichier, le token actuel sous forme de texte.
*/
void saveToken(const char* token);

/*	Fonction 	: LexError
	Description : Enregistre l'erreur dans un fichier, et ignore la ligne actuel du programme.
*/
void LexError(const char* message);

/* 	Fonction 	: ignoreWhiteSpaces
	Description : Ignore  les séparateurs comme les tabulations, les espaces et les nouvelles lignes.
*/
void ignoreWhiteSpaces();

/*	Fonction	: ignoreComment
	Description	: Ignore un seul commentaire.
*/
void ignoreComment();

/*	Fonction 	: getCurrentword
	Description : Lit tout un mot depuis le charactère actuel
*/
void getCurrentWord();

/*	Fonction 	: search_for_token
	Description : Reçoit une liste de tokens et un mot et cherche sa correspondence dans cette liste
*/
bool search_for_token();

/*	Fonction	: isNumber
	Description	: Construit le nombre et vérifie si c’est un INT, LONG, FLOAT, DOUBLE.
			  Sinon elle le traite comme un invalide Nombre.
*/
bool isNumber();

/*	Fonction	: isBloc
	Description	: Vérifie si le token correspond aux différents étages du programme : 
			   Libraries, Constants, Variables, Functions, Main
*/
bool isBloc();

/*	Fonction	: isReturn
	Description	: Vérifie si le token correspond au mot clé "return"
*/
bool isReturn();

/*	Fonction	: isString
	Description	: Construit le mot, et vérifie si respecte la forme suivante <" texte ">
*/
bool isString();

/*	Fonction	: isIdentifier
	Description	: Il n'y a pas de comparaison dans cette fonction, parceque dans ce cas
	tous les tests sur le token qui commence avec alphabet ont échoué, donc il ne reste que le déclaré comme Identificateur.
*/
bool isIdentifier();

/*	Fonction	: isDataType
	Description	: Deux types de données qui se déclare explicitement et qui sont <list, FILE>
*/
bool isDataType();

/*	Fonction	: isConditionOrLoop
	Description	: Vérifie si le Token appartient aux tokens réservés pour les conditions et les boucles.
*/
bool isConditionOrLoop();

/*	Fonction	: isCharacter
	Description	: Un token de type charactère respecte la forme suivante <'c'> avec c un charactère quelconque.
*/
bool isCharacter();

/*	Fonction	: isOperator
	Description	: Vérifie si c’est opérateur correspond à la division, la multiplication, la soustraction,
			  l’addition etc...
*/
bool isOperator();

/*	Fonction	: isSpecialSymb
	Description	: Vérifie si c’est un charactère spécial.
*/
bool isSpecialSymb();
```

## **2.2. Analyseur Syntaxique**
```c
/*	Fonction	: getToken
	Description : A chaque appel, la fonction getToken donne le token suivant.
*/
void getToken()

/*	Fonction	: error
	Description : S’assure qu’il n’y a pas d’erreurs syntaxiques. Dans l’autre cas elle enregistre 
	              un message d’erreur dans un fichier « error.txt » et saute les token reçu jusqu’au une fin 
		      de l’instruction erronée. 
*/
int error(char* message)

/*	Fonction	: program
	Description : Vérifie le token courrant , appelle les fonctions correspondantes au bloc qui représente le token   
*/
void program()

/*	Fonction	: libraries
	Description : Teste si l’expression représente soit la déclaration d’une librairie ou bien d’un header
*/
void libraries()

/*	Fonction	: constants
	Description : Vérifie la syntaxe de déclaration des constants dans le bloc constants()
*/
void constants()

/*	Fonction	: variables
	Description : Assure que la déclaration des variables est bien faite 
*/
void variables()

/*	Fonction	: functions
	Description : Teste si l’expression actuel représente une déclaration de fonction sous la forme :
	               Function(arguments){instructions}
*/
void functions()

/*	Fonction	: Insts
	Description : Appel la fonction Inst() , tanque cette dernière return true 
*/
void Insts()

/*	Fonction	: Inst
	Description : vérifie tous sorte d’instructions qui peuvent se produire et fait appel aux fonctions 
	              correspondantes à chaque instruction. 
*/
bool Inst()

/*	Fonction	: list
	Description : vérifie si l’affectation d’une donnée à un élément de la liste est valide 
*/
void list()
 
/*	Fonction	: callFunction
	Description : Teste si l’expression d’appel fonction avec ses arguments est valide.
*/
void callFunction()

/*	Fonction	: condition
	Description : Teste si l’expression actuel représente la syntaxe d’une instruction conditionnelle qui est sous cette forme : 
	                ( ID | CallFunction | Value ) Comp_Op ( ID | CallFunction | Value ) 
*/
void condition()

/*	Fonction	: decision
	Description : Teste si l’expression actuel représente une instruction conditionnelle sous la forme de : 
	               if (condition) {expressions} ou bien if (condition) {expressions} elif {expressions}
*/
void decision()

/*	Fonction	: loop
	Description : Teste si l’instruction courante représente l’une des trois instructions de boucle (voir grammaire) 
*/
void loop()

/*	Fonction	: expr
	Description : Vérifie si la syntaxe représentée dans la grammaire de l’expression est valide. Voir la grammaire de  « expr »;
*/
void expr()

/*	Fonction	: exprBegin
	Description : Vérifie si la syntaxe représentée dans le début de la grammaire de l’expression est valide. 
	               Si oui il passe le token suivant a la fonction expr();
*/
void exprBegin()

/*	Fonction	: term
	Description : Vérifie si la syntaxe représentée dans la grammaire de Term  est valide. Voir la grammaire de  « TERM »;
*/
void term()

/*	Fonction	: fact
	Description : Teste si le token actuel représente soit Id , NUM ou bien une expression  
*/
void fact()

/*	Fonction	: is_value
	Description : Vérifie si le type de données est parmi les types suivants {num , char, string,list ou bien FILE} 
*/
void is_value()

/*	Fonction	: main
	Description : Teste si l’expression actuel représente la déclaration de la fonction  main sous la forme : 
		      Main(arguments){instructions}
*/
void main()
```
</br>


# **4. Fonctionnement du Compilateur**

Le compilateur récupère en entrée le trajet complet du fichier où se trouve le programme écrit dans le language cbl, ce fichier aura l'extension .cbl. 

Avant d'entamer les étapes de compilation, le compilateur s'assure que le fichier est non vide, puis passe à la première étape qui est l'analyse lexicale. Le compilateur recourt à l'exécutable de cet analyseur et lui fournit le trajet du fichier programme. A la fin de cette étape on aura comme sortie un fichier contenant les erreurs, ainsi qu'un autre contenant les tokens générés par l'analyseur lexicale.

Dans le cas où le fichier erreur soit non vide, le compilateur procède comme suit : il renvoie à l'écran les erreurs trouvés ainsi que la ligne où se trouve, puis termine la compilation. Dans l'autre cas, le compilateur procède à la deuxième étape qui est l'analyse syntaxique, et de la même manière qu'auparavant, le compilateur fait appel à l'éxécutable de l'analyseur syntaxique en lui fournissant cette fois deux fichiers celui du programme et celui des tokens. 

Le compilateur attend la fin de l'exécution pour vérifier si des erreurs syntaxiques existent, dans ce cas ils les affichents et se termine. Dans l'autre cas on aura une compilation réussi.

</br>

# **5. Future Amélioration**

-	Ajout des qualificateurs qui détermine le champ de visibilité des variables et des fonctions ainsi que la durée de vie tel que les mots clés : public, private, static, automatic.
-	Ajout de l’analyseur sémantique.
-	Indiquer précisemment où se trouve l'erreur en indiquant la colonne et la ligne.
-	Ajout des fonctions prédéfinies standard.
-	Création du préprocesseur et ajout des mots clés des instructions macro tel que #define, #ifndef, #ifdef, #endif
-	Créer une application qui installera notre compilateur sur le système d'exploitation.


</br>

# **6. Conclusion**

Ce projet nous a permis de parfaitement comprendre la chaîne de compilation d’un code. Et nous a donné l’occasion de découvrir énormément de problèmes liés notamment à l’analyse, qui n’étaient pas aussi évidents dans la théorie du cours.

Nous estimons avoir passé environ 3 semaines complètes pour l’achèvement de ce compilateur. Les deux premiers jours on s’est focalisé sur le regroupement de la grammaire, ensuite les tâches se sont divisées pour l’implémentation des analyseurs. 

Nous ne pensions pas passer autant de temps sur la conception de la grammaire, qui nous a valu de recommencer plusieurs fois et de passer de nombreuses heures à chercher la bonne méthode pour lever les ambiguïtés, sans en soulever d'autres.

La difficulté en général réside dans l’implémentation de la grammaire lors la réalisation de l’analyseur syntaxique, ensuite la sémantique pourra être facilement vérifié en se basant sur la table de symbole généré par l’analyseur syntaxique.
