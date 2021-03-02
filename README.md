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
2.	Documentation
3.	Analyseur Lexicale
4.	Analyseur Syntaxique
5.	Fonctionnement du Compilateur
6.	Future Amélioration
7.	Conclusion

</br>

# **1. Grammaire**

Terminaux  | Règle
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

# **2. Documentation** 

## **2.1. Analyseur Lexicale**


```c
/*	Fonction 	: NextChar
	Description : Lit le prochain charactère et le retourne.
*/
char NextChar();

/*	Fonction 	: SaveToken
	Description : 
*/
void saveToken(const char* token);

/*	Fonction 	: LexError
	Description : S’assure qu’il n’y a pas d’erreurs lexicales. Dans l’autre cas elle retourne un message d’erreur.
*/
void LexError(const char* message);

/* 	Fonction 	: ignoreWhiteSpaces
	Description : Ignore  les séparateurs comme la tabulation, les espaces et les nouvelles lignes.
	Arguments :  NULL
*/
void ignoreWhiteSpaces();

/*	Fonction	: ignoreComment
	Description	: Ignore  les commentaires.
*/
void ignoreComment();

/*	Fonction 	: getCurrentword
	Description : Lit le mot précédent	
*/
void getCurrentWord();

/*	Fonction	: isNumber
	Description	: Construit le nombre et vérifie si c’est un entier ou un réel. Sinon elle le traite comme un invalide Nombre, et arrête le programme.
*/
bool isNumber();

/*	Fonction	: isBloc
	Description	: 
*/
bool isBloc();

/*	Fonction	: isReturn
	Description	: 
*/
bool isReturn();

/*	Fonction	: isString
	Description	: Construit le mot, et vérifie si c’est un mot réservé pour la fonction, les décisions, les boucles ou pour le vecteur. Sinon elle test si c’est un appel de fonction où le considère comme un identificateur.
*/
bool isString();

/*	Fonction	: isIdentifier
	Description	: 
*/
bool isIdentifier();

/*	Fonction	: isDataType
	Description	: 
*/
bool isDataType();

/*	Fonction	: isConditionOrLoop
	Description	: 
*/
bool isConditionOrLoop();

/*	Fonction	: isCharacter
	Description	: 
*/
bool isCharacter();

/*	Fonction	: isOperator
	Description	: Vérifie si c’est opérateur tel la division, la multiplication, la soustraction, l’addition.
*/
bool isOperator();

/*	Fonction	: isSpecialSymb
	Description	: Vérifie si c’est un charactère spécial, et en cas où elle trouve les guillemets, elle vérifie si c’est un texte.
*/
bool isSpecialSymb();

/*	Fonction	: search_for_token
	Description	: 
*/
bool search_for_token(const char *word, const char **list, const char **listName, int size_of_list);
```

## **2.2. Analyseur Syntaxique**
```c

```
</br>


# **3. Fonctionnement du Compilateur**
# **4. Future Amélioration**


# **5. Conclusion**

Ce projet nous a permis de parfaitement comprendre la chaîne de compilation d’un code. Et nous a donné l’occasion de découvrir énormément de problèmes liés notamment à l’analyse, qui n’étaient pas aussi évidents dans la théorie du cours.

Nous estimons avoir passé environ 3 semaines complètes pour l’achèvement de ce compilateur. Les deux premiers jours on s’est focalisé sur le regroupement de la grammaire, ensuite les tâches se sont divisées pour l’implémentation des analyseurs. 

Nous ne pensions pas passer autant de temps sur la conception de la grammaire, qui nous a valu de recommencer plusieurs fois et de passer de nombreuses heures à chercher la bonne méthode pour lever les ambiguïtés, sans en soulever d'autres.

La difficulté en général réside dans l’implémentation de la grammaire lors la réalisation de l’analyseur syntaxique, ensuite la sémantique pourra être facilement vérifié en se basant sur la table de symbole généré par l’analyseur syntaxique.
