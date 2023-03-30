# RayTracingToy
Pràctica 1 - GiVD 2022-23

En aquest fitxer cal que feu l'informe de la pràctica 1.

## Equip:
**F02**
* Pau Baldillou Salse
* Pau Hernando Màrmol
* Esther Ruano Hortoneda
* Núria Torquet Luna

### Features (marqueu les que heu fet i qui les ha fet)
- Fase 0

    S'ha decidit que en aquesta fase inicial tots els integrants del grup realitzin totes les tasques per tal de familiaritzar-se amb la pràctica. Per tant, han participat tots els integrants del grup en la implementació de cada feature
    - [X] Background amb degradat
        - Tots els integrants
    - [X] Color Shading
        - Tots els integrants
    - [X] Normal Shading
        - Tots els integrants
    - [X] Depth Shading
        - Tots els integrants
    - [X] Intersecció amb l'escena
        - Tots els integrants
- Fase 1
    - Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [X] Hit Box
          - Pau Hernando
        - [X] Hit Triangle
          - Pau Baldillou
        - [X] Hit Malla
          - Pau Baldillou
          - Pau Hernando
    - Creació de REAL DATA
        - [X] FITTED PLANE: Pla de terra
          - Núria Torquet
        - [X] Transformacions Translació i Escalat amb gizmos esferes
          - Esther Ruano
          - Núria Torquet
        - [X] Gizmo de Box
          - Esther Ruano
        - [X] Noves dades
          - Esther Ruano
- Fase 2
    - Pas 1
        - [X] Afegir numSamples i Gamma correction
            - Pau Hernando
    - Pas 2
        - [X] Implementar Blinn-Phong Shading
            - Núria Torquet
        - [X] Implementar Phong Shading
            - Esther Ruano
        - [X] Implementar Cel Shading
            - Pau Baldillou
    - Pas 3
        - [X] Implementar Blinn-Phong Shadow
            - Núria Torquet
        - [X] Implementar Phong Shadow
            - Esther Ruano
        - [X] Implementar Cel Shadow
            - Pau Baldillou
        - [X] Implementar Color i Normal Shadow
            - Pau Hernando
    - Pas 4
        - [X] Recursió per rajos secundaris
            - Núria Torquet
        - [X] Nou material metàl·lic
            - Pau Baldillou
        - [X] Recursió per objectes transparents
            - Núria Torquet
        - [X] Nou material transparent
            - Esther Ruano
    - Pas 5
        - [ ] Adapta la visualització per mostrar dades des d'un fitxer
 - Fase 3
    - Pas 1
        - [X] Afegir nou material textura al pla base
            - Esther Ruano
    - Pas 2
        - [X] Prova amb diferents jocs de dades i mapes
            - Esther Ruano
    - Pas 3
        - [X] Genera diferents jocs de dades i mapes
            - Esther Ruano
    - Pas 4
        - [ ] Genera noves escenes i resultats finals de la pràctica
       
 

- Parts opcionales: 
  - [X] Cilindres
    - Esther Ruano
  - [ ] Escena CSG 
  
  - [X] Més d'una propietat en les dades reals
    - Esther Ruano
  - [X] Mapeig de les dades reals en una esfera
    - Núria Torquet
  - [ ] Afegir nous objectes paramètrics  
  - [X] Llums direccionals i spotlight
    - Pau Baldillou
    
    
### Explicació de la pràctica    
  * **Organització de la pràctica**
    * descriu com us heu organitzat
  
  * **Decisions a destacar**
    * Comenteu les decisions que heu pres 
    * **Cel Shading**. Hem implementat el Cel shading per un nombre arbitrari de tons per cada objecte. Aquests tons es llegeixen del material de l'objecte al JSON de l'escena. Necessites afegir informació al material? Sí, hem creat una classe abstracta "ToonMaterial". Aquesta classe hereta de Material i alhora és la mare de tots els altres materials. En aquesta classe hem afegit l'atribut "gradientColor" que és un vector de colors. Hem hagut d'implementar els mètodes de llegir i escriure a fitxer. Aquestes funcions criden a les respectives funcions de Material, però a més llegeixen o escriuen el vector de tonalitats. 
    A part del Cel shading com a tal, hem implementat també les extensions explicades a classe, on hem incorporat la component especular, i la llum ambient. A més, hem afegit la silueta dels objectes, que surten ressaltats dins l'escena.
    Per admetre un nombre arbitrari d'intervals, per calcular el color en cada punt calculem $t = \lfloor n \cdot x \rfloor$ on x ès el cosinus entre l'angle de llum i la normal, i n el nombre d'intervals. Aleshores t és l'índex de l'interval corresponent. En cas que el cosinus sigui 1, hem decidit posar el color més clar del que disposem.
    * **SceneFactoryData**: //explicar quines dimensions i translacions hem decidit.
    
    * **Llum direccional**. Hem implementat una nova classe de llum, la direccional. Aquesta no té posició, doncs està situada a l'infinit. A més, la seva atenuació sempre és 1, pel mateix motiu. Té 2 atributs propis: intensitat i direcció.
    * **Llum spotlight**. Hem implementat una nova classe de llum, la spotlight (o focus). Al igual que la point light, aquesta sí que té posició. I similarment a la direccional, també té una direcció, ja que, a diferència de la point light, no il·lumina en totes direccions. Les llums spotlight, només il·luminen en una regió cònica amb vèrtex la posició de la llum i direcció la recta que seria l'eix de revolució. El con es defineix amb l'angle d'il·luminació (que és l'angle entre la direcció de la llum i la vora del con). Per tot això, la nova classe té com a atributs la posició, la direcció, l'angle de tall (a partir del qual considerarem que un punt no està il·luminat) i l'exponent (que controla com concentrada és la llum).
    
    
        <img src="https://user-images.githubusercontent.com/69910092/227730288-714c1fe8-d328-42c4-b775-66b53943805a.png"> 
        
        Per tal de controlar des de la llum, quins punts pot il·luminar, hem canviat la funció que retorna l'atenuació. Aquesta serà 0 en els putns que queden fora del con. Pel punts que queden dins del con, és la següent funció: $\cos(\theta)^{\alpha}$ on $\theta$ és l'angle entre la direcció i el vector que uneix el punt que volem il·luminar i la posició de la llum, i $\alpha$ és l'exponent que guarda la llum.
    
### Resposta a les preguntes plantejades
* **Fase 0**: 
    * **3.b. Quina escena es té carregada? Qui la crea? Quin setup té la classe? Des d'on es crea?**
        La classe RayTracer és la responsable de trçar rajos per a renderitzar imatges d'una escena en 3D. La imatge és emmagatzemada en un objecte QImage, que es passa com a paràmetre al constructor de la classe RayTracer. El mètode run() de la classe RayTracer conté el bucle principal del renderitzat, on cada píxel de la imatge es renderitza mitjançant el llançament de rajos. Els objectes necessaris per a la renderització, com ara el setup i l'escena, s'obtenen de la classe Controller, utilitzant mètodes estàtics. Per tant, la classe Controller és responsable de crear i gestionar la configuració de la renderització i l'escena, i es fa servir per la classe RayTracer per obtenir aquestes dades.
    * **3.c. Per què es veu un degradat en l'escena? A quin mètode es calcula aquest color?**
        Si prems el botó de Trace, es veu un degradat perquè el mètode RayPixel() de la classe RayTracer retorna un degradat en cas que l'opció de "background" estigui activada en la configuració del renderitzat.

        En aquest cas, el degradat es calcula a la part superior del mètode RayPixel(), on es normalitza la direcció del raig i s'utilitza per calcular el color de fons. El càlcul es fa mitjançant la creació d'un vector que té les seves components normalitzades i, a continuació, es transforma aquest vector a un color RGB de 24 bits.
    * **3.d. Si desactives el flag de background, i tornes a fer Trace, quin efecte et trobes? Per què? Pots veure com ha arribat el flag de background al teu RayTracer?**
        Si desactives el flag de background i tornes a fer Trace, es veurà una imatge negra sense cap mena de degradat. Això és degut a que el càlcul del color de fons només es fa si el flag de background està activat. En desactivar-lo, el color de fons es posa a negre per defecte.

        El flag de background es pot trobar al mètode init() de la classe RayTracer, on es comprova si aquesta opció està activada en la configuració del renderitzat. Aquesta configuració es carrega en el constructor del RayTracer a través del controlador, que obté la configuració i l'escena corresponents.
    * **3.e. En quina variable trobes els colors per fer el degradat?**
        Es poden obtindre els colors de background superior i inferior fent les següents crides amb la variables setup:
            setup->getTopBackground();
            setup->getDownBackground();
    * **3.f. I si volguessis canviar els colors del degradat? On els canviaries?**
        A la interfície seleccionaria uns altres colors de la paleta, i amb aquests canvis obtindria uns nous valors de retorns en els getters de background de setup.
    * **3.g. Des del menú de File pots crea una esfera unitària amb centre al punt (0, 0, 0). Si prems Trace, no la veuràs, per què?**
        La raó per la qual no es veu la nova esfera és que encara no s'ha implementat la intersecció amb objectes de l'escena en el càlcul de colors per cada píxel. El mètode RayPixel actual només retorna el color del degradat de fons, i no fa cap comprovació per veure si el raig interseca amb algun objecte de l'escena. Per tant, fins que no s'implementi la intersecció amb objectes de l'escena, no es podrà veure cap objecte nou afegit a l'escena.
    * **3.h. Com pots accedir a les diferents estratègies? A quina variable pots aconseguir l’estratègia a cridar? Com es crea aquesta estratègia des del menú?**
        Mitjançant la variable setup, cridant el mètode getShadingStrategy() per obtenir el shading que s'està aplicant. I per aplicar el shading concret a l'escena, amb el mètode shading. Aquest es troba definit de forma virtual a la classe ShadingStrategy i implementat de forma diferent en cada classe shading.
        Per a crear aquesta estratègia des del menú, quan l'usuari clica un dels shadings, en la MainWindow es llença el senyal de que s'executi activaXXShading(), localitzat en Builder. Builder crida a Controller per a que creï una instància del shading XX i estableixi en la variable setup que el shading a aplicar sigui aquest (setShadingStrategy). Aleshores en el mètode rayPixel de RayTracer es comprova des de setup quin shading s'ha d'aplicar i es crida el mètode shading corresponent a la classe.
    * **3.i. Com faràs per a crear una nova estratègia de shading?**
        S'ha de crear una nova classe per a gestionar el shading que heredi de ShadingStrategy. A continuació s'implementa el mètode virtual shading() amb la implementació concreta del shading que es vulgui. S'ha d'afegir aquest nou tipus a l'enum SHADING_TYPES del fitxer ShadingFactory. I s'ha d'inicialitzar correctament amb l'ajuda de l'enum a la classe ShadingFactory.
    * **3.j. Com aconsegueixes que els colors del depth shading estiguin normalitzats?** 
        Es pot dividir la distància entre el punt de vista (lookFrom) i el punt d'intersecció amb l'objecte per un valor de distància màxim predefinit, per evitar la sobreexposició dels píxels llunyans. En el nostre cas, s'ha establert que sigui 10. Si el valor màxim de distància és 10 unitats, qualsevol distància superior a 10 es considerarà el màxim i es normalitzarà per aquest valor.
        Per tant,  es normalitza la distància real (distance) dividint-la pel valor màxim de distància (max_distance). Això produeix un valor entre 0 i 1, que representa la distància normalitzada. Aquesta normalització és important per garantir que la funció de shading es comporti de manera coherent independentment de la distància entre el punt de vista i el punt d'impacte.
    * **3.k. Per què veus només una esfera? On està situada a la teva escena? Amb quin radi? Per què? Per què és lila i no de color "kd": [0.7,0.6,0.5] com posa el fitxer?**
        El fitxer de dades real data0.json defineix una escena amb només una esfera perquè només hi ha un element en la llista "attributes". Aquest element té un nom "temperatura", un gizmo "sphere" i un únic punt de dades en la posició -2,-1 amb un valor de 0.5. Aquest punt es representa com una esfera perquè el gizmo de l'atribut és "sphere".
        L'esfera es troba a la posició (-2, 0, -1) a la nostra escena virtual, ja que el fitxer de configuració especifica que el rang de coordenades en la dimensió Y és de 0 a 2.0. El radi de l'esfera es defineix per defecte a 0.5, ja que no s'especifica cap valor de radi a la configuració de l'atribut.
        La raó per la qual la esfera és lila en lloc de tenir el color especificat per "kd": [0.7, 0.6, 0.5] és perquè el valor de "colorMap" a l'atribut és "COLOR_MAP_TYPE_INFERNO". Això significa que es fa servir un mapa de colors anomenat "inferno" per assignar colors a l'atribut segons el seu valor. El mapa de colors "inferno" és una gradació de colors que comença amb tons de blau i morat, passa a través de vermells i grocs brillants, i acaba amb tons de groc verdós. En aquest cas, el valor de 0.5 es correspon a un to de morat en el mapa de colors "inferno", de manera que l'esfera es veu lila.

* **Fase 1**:
    * **Pas 3**:
        **3.a. Modifica la classe ```ObjectFactory``` per a carregar i crear malles poligonals en fora de ```Mesh```. En aquest cas, el ```read``` de la classe ```Mesh``` ja està implementat. Quan penses que és millor crear els triangles de la malla?**
            Ho hem implementat de manera que no cal crear els triangles, doncs ho calculem directament amb les cares. Tanmateix, en cas que volguéssim fer servir els triangles, els calcularíem quan fem el ```read```, desprès de llegir les cares. D'aquesta manera, només cal fer-ho una vegada i és quan es carrega l'objecte, i no cada cop que volem fer hit. Si calculessim els triangles quan els necessitem al ```hit```, aleshores el nostre algorisme seria molt lent.
        ** 3.b. Implementa les dues possibilitats, la de la *bounding box* i la de la *bounding sphere*. Quina creus que teòricament és millor? Com funcionen en realitat?**
            ... tests ... En realitat, tot funcionarà de la forma de l'objecte. Si la nostra malla té una forma esfèrica, la *bounding sphere* serà més similar, fent-la més eficient a l'hora de calcular el hit previ. En canvi, si la malla és allargada (un el·lipsoide per exemple), la caixa serà millor. En la implementació actual, les caixes estan sempre aliniades amb els eixos. Això també podria fer que per una figura cúbica rotada de la manera adequada, la *bounding sphere* fos millor. 

* **Fase 2**:
    * **Pas 1**:
        * **2. On afegiries un atribut ```numSamples``` que defineixi el nombre de rajos per píxel i així controlar aquest fet?**

        * **3. Per aclarir la imatge, s'utilitza una correcció del color final calculat. Aquest fet s'anomena *Gamma Correction*. Es tracta de fer l'arrel quadrada de cada canal del color just abans de pintar-lo. On faràs aquesta correcció?**
    
    * **Pas 2**:
        * **3. Implementa *Phong Shading*. Què necessites canviar?**
            En general, la diferència més notable entre la implementació de Blinn-Phong shading i Phong shading és la forma en què es calcula el component especular. Mentre que Blinn-Phong utilitza el vector de vista i el vector de mitjana com a paràmetres per a la funció de distribució especular, Phong shading utilitza el vector de reflexió i el vector de vista.
            Concretament, la fórmula per al component especular en Blinn-Phong shading és:
            ```(info.mat_ptr->Ks * light->getIs() * pow(std::max(dot(N,H), 0.0f), info.mat_ptr->beta)) * depthAttenuation;```
            Mentre que en Phong shading és:
            ```(info.mat_ptr->Ks * light->getIs() * pow(std::max(dot(R,V), 0.0f), info.mat_ptr->shininess)) * depthAttenuation;```
            A més, en Blinn-Phong s'utilitza un paràmetre "beta" per controlar la distribució especular, mentre que en Phong s'utilitza el paràmetre "shininess" per controlar la concentració del brillantor. Ara bé, a la pràctica s'ha utilitzat el mateix valor per als paràmetres "beta" i "shininess".        
        
        * **4. Implementa *Cel Shading*. Necessites afegir informació en el material?**
            Sí. Cal afegir els diferents colors (més foscos i més clars) que volem que tingui cada material. Això ho hem fet creant una classe abstracta ```ToonMaterial``` que conté un vector de colors (vec3) de mida arbitrària (```colorGradient```). Aquests colors, ordenats segons la seva claror, són els que s'utilitzen per pintar les figures, depenent de l'angle d'incidència de la llum. La classe ```ToonMaterial``` hereta de ```Material```. Alhora, tots els altres materials són classes filles de ```ToonMaterial```.
            
    * **Pas 3**:
        * **2. En el cas que hi hagi un objecte entre la llum i el punt on s'està calculant la il·luminació, quina component de la fórmula Blinn-Phong s'haurà de tenir en compte?**
        En el cas que hi hagi un objecte entre la llum i el punt on s'està calculant la il·luminació, la component que s'haurà de tenir en compte és la difusa, ja que és la que es veu afectada per la presència d'ombres.
    * **Pas 4**:
        * **3. Tingues en compte que necessitaràs la *nu_t* per a definir el material transparent. Tot i que ara el codi no està llegint aquesta nu_t, on hauries de llegir-la?**
        A la classe Material, al mètode read() s'ha de llegir també el paràmetre nu-t; si el fitxer json conté el paràmetre nut i aquest valor és de tipus double, s'ha d'assignar el valor a la variable nu-t del material.
        
        * **Per què si tens el MAX_DEPTH a 1, l'esfera no es veu transparent?**
        Si tenim el valor MAX_DEPTH a 1, això significa que només es farà un rebot de llum, és a dir, només es seguirà un raig de llum després de xocar amb l'objecte. Per tant, si l'objecte és opac, no es veurà res més enllà d'aquest objecte, ja que només es considera un únic rebot de llum.

        * **Si assignes el color ambient global en lloc del de *background* en els rajos secundaris que no intersequen amb res, com et canvia la visualització? Raona el per què.**
        Si assignem el color ambient global en lloc del color de fons (background) en els rajos secundaris que no intersequen amb cap objecte, la visualització canvia perquè tots els píxels que no estan directament en la línia de visió dels objectes de la nostra escena reben el mateix color ambient, creant una mena d'il·luminació uniforme en la imatge. Això pot ser útil per crear un efecte d'illuminació ambiental a la nostra escena, però també pot provocar que la imatge aparegui una mica "plana" i sense profunditat.

        * **Raona per què en aquests casos l'escena es veu més clara**
        Si no es pondera el color local amb (1- colorScattered) els materials transparents no absorveixen la llum que travessa l'objecte, cosa que significa que la llum passa per ells sense ser atenuada. Això pot fer que les escenes semblin més brillants i clares en general, però també afecta negativament en la percepció de la profunditat i oclusió de la imatge.
        

    
    
### Screenshots de cada fase
* **Fase 0**:
   - Intersecció dels rajos amb una esfera
    
    <img src="screenshots/FASE_00/05_esfera_color_shading.png" alt="Color shading una esfera" width="300">
    <img src="screenshots/FASE_00/06_esfera_normal_shading.png" alt="Normal shading una esfera" width="300">
    <img src="screenshots/FASE_00/10_esfera_depth_shading.png" alt="Depth shading una esfera" width="300">
    
    - Intersecció dels rajos amb dues esferes
    
    <img src="screenshots/FASE_00/08_virtualscene_color_shading.png" alt="Color shading dues esferes" width="300">
    <img src="screenshots/FASE_00/11_virtualscene_depth_shading.png" alt="Depth shading dues esferes" width="300">


* **Fase 1**: 

* **Fase 2**:
    * **Pas 2. Considera les llums puntuals a la teva escena i implementa el shading de Blinn-Phong:**
        - Blinn Phong Shading usant el fitxer twoSpheres.json i el fitxer de setup setupRenderTwoSpheres.json

            a. Si només es calcula la component ambient
            <img src="screenshots/FASE_02/SS/BP_ambient.png" alt="Blinn-Phong amb component ambient" width="300">
            b. Si només es calcula la component difosa
            <img src="screenshots/FASE_02/SS/BP_difuse.png" alt="Blinn-Phong amb component difosa" width="300">
            c. Si només es calcula l'especular
            <img src="screenshots/FASE_02/SS/BP_especular.png" alt="Blinn-Phong amb component especular" width="300">
            d. Ara les tres juntes
            <img src="screenshots/FASE_02/SS/BP_tres.png" alt="Blinn-Phong amb les tres components" width="300">
            e. I afegint atenuació amb profunditat
            <img src="screenshots/FASE_02/SS/BP_atenuacio.png" alt="Blinn-Phong amb atenuació amb profunditat" width="300">
            f. I afegint l'ambient global
            <img src="screenshots/FASE_02/SS/BP_global.png" alt="Blinn-Phong amb l'ambient global" width="300">


        - Phong Shading usant el fitxer twoSpheres.json i el fitxer de setup setupRenderTwoSpheres.json
            a. Si només es calcula la component ambient
            <img src="screenshots/FASE_02/SS/P_ambient.png" alt="Phong amb component ambient" width="300">
            b. Si només es calcula la component difosa
            <img src="screenshots/FASE_02/SS/P_difuse.png" alt="Blinn-Phong amb component difosa" width="300">
            c. Si només es calcula l'especular
            <img src="screenshots/FASE_02/SS/P_especular.png" alt="Phong amb component especular" width="300">
            d. Ara les tres juntes
            <img src="screenshots/FASE_02/SS/P_tres.png" alt="Phong amb les tres components" width="300">
            e. I afegint atenuació amb profunditat
            <img src="screenshots/FASE_02/SS/P_atenuacio.png" alt="Phong amb atenuació amb profunditat" width="300">
            f. Phong Shading no té llum ambient global, només té component ambient local


        - Cel Shading i les seves ombres (Pas 3)

            ![Captura de Pantalla 2023-03-20 a las 21 14 03](https://user-images.githubusercontent.com/69910092/226461156-e1d1c1fa-fd01-4c8f-91ab-8ff6ee3161ef.png "Component ambient") 

            Component ambient amb nSamples = 1

            ![Captura de Pantalla 2023-03-20 a las 21 15 35](https://user-images.githubusercontent.com/69910092/226461161-db5e0a35-dc12-4920-bf2b-e3f71a749348.png "Component 'Toon'")

            Component "Toon": només els colors de les tonalitats. Això correspon a com es veu sense extensions.

            ![Captura de Pantalla 2023-03-20 a las 21 17 08](https://user-images.githubusercontent.com/69910092/226461163-1616e794-7a76-4caf-9399-71f432c08789.png "Component especular") 

            Component especular amb shininess = 100 (es veu una taca blanca molt petita)

            ![Captura de Pantalla 2023-03-20 a las 21 18 23](https://user-images.githubusercontent.com/69910092/226461167-55b3f04f-7ed9-48d5-92d1-a6753c4be73b.png "Rim")

            Rim (la silueta)

            ![Captura de Pantalla 2023-03-20 a las 21 19 39](https://user-images.githubusercontent.com/69910092/226461168-cd62da50-5270-47e1-bef1-13547391bb33.png "Tot junt sense ombra")

            Tot junt sense ombra amb nSamples baix.

            ![Captura de Pantalla 2023-03-20 a las 21 25 00](https://user-images.githubusercontent.com/69910092/226461171-1998cbfa-be59-46b9-bdde-08ea7d507406.png  "Tot junt sense ombra II")

            Tot junt sense ombra amb més samples.

            ![Captura de Pantalla 2023-03-20 a las 21 25 11](https://user-images.githubusercontent.com/69910092/226461175-7b8918c1-03bd-4f05-a1f9-a986ca4960cd.png "Tot junt amb ombra") 

            Tot junt amb ombra.

            ![Captura de Pantalla 2023-03-20 a las 21 36 51](https://user-images.githubusercontent.com/69910092/226461179-01a6ec7b-fa1b-4e82-94d6-5fb12ca44a55.png "Tot junt, bola vermella II") 

            La mateixa imatge amb una bola vermella, ombra i 10 samples.

            ![Captura de Pantalla 2023-03-20 a las 21 36 41](https://user-images.githubusercontent.com/69910092/226461176-0803796c-25bb-4497-a74b-0646fc1fec5b.png "Tot junt, bola vermella") 

            La mateixa imatge amb una bola vermella i més samples.
    
    * **Pas 3. Afegeix ombres**

        - Blinn Phong Shadow des de dos punts de vista
        
            <img src="screenshots/FASE_02/SS/BP_shadow01.png" alt="Blinn-Phong shadow amb x=0" width="300">
            <img src="screenshots/FASE_02/SS/BP_shadow02.png" alt="Blinn-Phong shadow amb x=2" width="300">
            
        - Phong Shadow des de dos punts de vista
        
            <img src="screenshots/FASE_02/SS/P_shadow01.png" alt="Blinn-Phong amb les tres components" width="300">
            <img src="screenshots/FASE_02/SS/P_shadow02.png" alt="Blinn-Phong amb les tres components" width="300">
            
        - Normal Shadow
        
            <img src="screenshots/FASE_02/SS/NORMAL_shadow.png" alt="Blinn-Phong amb les tres components" width="300">
            
        - Visualització del fitxer spheres.json amb el setup setupRenderSpheres.json
        
            <img src="screenshots/FASE_02/SS/visualitzacio_esferes.png" alt="Visualització del fitxer sheres" width="300">
            
        - Escena més complexa modificant el fitxer spheres.json amb 10 objectes
        
            <img src="screenshots/FASE_02/SS/visualitzacio_alt.png" alt="Visualització del fitxer multiple_spheres" width="300">
            
            
    * **Pas 4: Afegir recursió al mètode RayPixel per a tindre en compte els rajos reflectits**
        
        - Resultats obtinguts amb dues esferes amb material Lambertià, valors de Max Depth 1, 3 i 10 i nombre de samples 10. Shading Blinn-Phong, fitxer de setup setupRenderTwoSpheres.json i fitxer de dades twoSpheres.json
        
        <img src="screenshots/FASE_02/RRR/RRR_01.png" alt="Amb Max Depth 1" width="300">
        <img src="screenshots/FASE_02/RRR/RRR_02.png" alt="Amb Max Depth 3" width="300">
        <img src="screenshots/FASE_02/RRR/RRR_03.png" alt="Amb Max Depth 10" width="300">
        
        - Resultats obtinguts al assignar la intensitat ambient global als rajos secundaris que no intersequen amb l'escena.
    
        <img src="screenshots/FASE_02/RRR/RRR_04.png" alt="Amb Max Depth 1" width="300">
        <img src="screenshots/FASE_02/RRR/RRR_05.png" alt="Amb Max Depth 10" width="300">
    
    
        - Resultats obtinguts al visualitzar dues esferes lambertianes i una de metàl.lica, amb valors de Max Depth 1, 3 i 10 i nombre de samples 10. Shading Blinn-Phong, fitxer de setup setupRenderSpheres.json i fitxer de dades threeSpheres.json
    
        <img src="screenshots/FASE_02/RRR/RRR_06.png" alt="Amb Max Depth 1" width="300">
        <img src="screenshots/FASE_02/RRR/RRR_07.png" alt="Amb Max Depth 3" width="300">
        <img src="screenshots/FASE_02/RRR/RRR_08.png" alt="Amb Max Depth 10" width="300">

        - Visualitzacions dels shadings Phong, Cel i Normal amb mateix setup file i fitxer de dades.
            - Phong Shading:
            
                <img src="screenshots/FASE_02/RRR/RRR_20.png" alt="Amb Max Depth 1" width="300">
                <img src="screenshots/FASE_02/RRR/RRR_21.png" alt="Amb Max Depth 3" width="300">
                <img src="screenshots/FASE_02/RRR/RRR_22.png" alt="Amb Max Depth 10" width="300">

            - Normal Shading:
            
                <img src="screenshots/FASE_02/RRR/RRR_23.png" alt="Amb Max Depth 1" width="300">
                <img src="screenshots/FASE_02/RRR/RRR_24.png" alt="Amb Max Depth 3" width="300">
                <img src="screenshots/FASE_02/RRR/RRR_25.png" alt="Amb Max Depth 10" width="300">
            
            - Cel Shading:

                <img src="screenshots/FASE_02/RRR/RRR_26.png" alt="Amb Max Depth 1" width="300">
                <img src="screenshots/FASE_02/RRR/RRR_27.png" alt="Amb Max Depth 3" width="300">
                <img src="screenshots/FASE_02/RRR/RRR_28.png" alt="Amb Max Depth 10" width="300">
    
    * **Pas 5: Afegir recursió al mètode RayPixel per a tindre en compte objectes transparents**
        
        - Resultats obtinguts al visualitzar el fitxer spheresMetalTransp.json i el setupRenderTwoSpheres.json. Max depth pren els valors 1, 2 i 3, i el nombre de samples és 10.
        
            <img src="screenshots/FASE_02/RRR/RRR_09.png" alt="Amb Max Depth 1" width="300">
            <img src="screenshots/FASE_02/RRR/RRR_10.png" alt="Amb Max Depth 2" width="300">
            <img src="screenshots/FASE_02/RRR/RRR_11.png" alt="Amb Max Depth 3" width="300">
    
        - Modificant el punt de vista amb valors de lookFrom (-5, 0, 1) i lookAt (-2, 0, 0) i canviat el valor de kd a [0.7, 0.7, 0.7]
    
            <img src="screenshots/FASE_02/RRR/RRR_12.png" alt="Amb Max Depth 3" width="300">
        
        - Visualitzacions amb el fitxer fourSpheres.json i el setupRenderFourSpheres.json i nivells de recursivitat MAXDEPTH = 1, 2, i 4. Nombre de samples és 10.
        
            <img src="screenshots/FASE_02/RRR/RRR_13.png" alt="Amb Max Depth 1" width="300">
            <img src="screenshots/FASE_02/RRR/RRR_14.png" alt="Amb Max Depth 2" width="300">
            <img src="screenshots/FASE_02/RRR/RRR_15.png" alt="Amb Max Depth 4" width="300">
            
        - Visualització de l'escena anterior fent que els rajos secundaris que no intersequen amb l'escena rebin el color ambient global.
        
            <img src="screenshots/FASE_02/RRR/RRR_16.png" alt="Amb Max Depth 1" width="300">
    
        - Visualització de l'escena anterior fent que no es ponderi el color local.
    
            <img src="screenshots/FASE_02/RRR/RRR_17.png" alt="Amb Max Depth 1" width="300">
            <img src="screenshots/FASE_02/RRR/RRR_18.png" alt="Amb Max Depth 2" width="300">
            <img src="screenshots/FASE_02/RRR/RRR_19.png" alt="Amb Max Depth 4" width="300">
    
        
* **Fase 3**:
    - **Amb el fitxer de setup setupDataEuropa.json quina de les dues imatges obtens? Raona per què.**
    
      Ens trobem en la situació de la dreta: és fàcil de veure, si mirem dadesEuropa.json, trobem que el pla correspon a l'equació {y=-1}, i està afitat per valors d'x i z entre -50 i 50. Com que és un fitxer de tipus RealData, per les esferes en coneixem el valor x i z del centre, i li donem valor y = 0 per defecte al centre. A més, pel nostre escalat, l'esfera més gran tindrà radi = 1. Per tant, cap de les esferes travessarà el pla com es veu a la imatge 1. 
      
    - **Qui calcularà les coordenades (u, v) del punt d’intersecció amb el pla?**
    
      Les calcularà la classe fitted plane i les desarà a l'atribut uv de la classe HitInfo, perquè hi pugui accedir el shading corresponent.
      
    - **Quina de les dues visualitzacions obtens? **
    
      Obtenim la segona visualització:
      
      ![imagen](https://user-images.githubusercontent.com/80753129/227035406-78d659d9-ff69-4768-8ae6-e33469b71009.png "Visualització Fase 3 1.3")
      
    - **Visualitzacions associades a dadesBCN_Zoom i dadesBCN**
       ![imagen](https://user-images.githubusercontent.com/80753129/227382648-703f0c93-9b22-420a-bb83-43fcc99a51b6.png)
  
    - **Prova també a posar les esferes metàl·liques i transparents, com feies a la Fase 2**
      
      Hem afegit quatre esferes transparents, i n'adjuntem les visualitzacions a continuació. Corresponen al fitxer dadesEuropaCustom.json, amb el setup setupDataEuropa.json
      
      ![imagen](https://user-images.githubusercontent.com/80753129/227384815-20342c98-d36f-4ebe-b27a-165c915cb3e7.png)

    - **Cal incloure com a mínim un nou joc de dades amb un mínim d’una propietat, amb un mínim de 15 dades i amb algun altre mapa**
    
      Creem un arxiu anomenat fase31.json i un setupFase31.json. Modelen la població d'ànec xiulador (esferes transparents), així com l'ànec blanc (box metal·lics), l'ànec griset (cilindres lambertians) al Delta de l'Ebre.
      ![imagen](https://user-images.githubusercontent.com/80753129/227723119-793a260c-6e7d-4864-8bd6-a15be05aa83b.png)

    


* **Opcionals**:
    - Directional Light
    
    ![Captura de Pantalla 2023-03-20 a las 22 07 05](https://user-images.githubusercontent.com/69910092/226466772-27d20596-31ae-4b0b-ae55-39f110759f46.png "Directional Light (-1, -0.6, -0.3)") 
    
    ![Captura de Pantalla 2023-03-20 a las 22 09 24](https://user-images.githubusercontent.com/69910092/226466784-43696e94-f314-4e6f-b6ce-b553b32f6b78.png "Directional Light (1, -0.6, -0.3)")

    El groc clar que es veu "independentment d'on ve la llum" és el rim de la bola gran.
    

* **Més visualitzacions**:

   * Per totes les imatges, incluiu aqui la imatge obtinguda i els fitxers de dades i de configuració que heu fet servir
