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
        - [ ] Recursió per rajos secundaris
            - Núria Torquet
        - [X] Nou material metàl·lic
            - Pau Baldillou
        - [X] Recursió per objectes transparents
            - Núria Torquet
        - [X] Nou material transparent
            - Esther Ruano
    - Pas 4
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
  - [X] Llums direccionals
    - Pau Baldillou

  
    
    
### Explicació de la pràctica    
  * **Organització de la pràctica**
    * descriu com us heu organitzat
  
  * **Decisions a destacar**
    * Comenteu les decisions que heu pres 
    * **Cel Shading**. Hem implementat el Cel shading per un nombre arbitrari de tons per cada objecte. Aquests tons es llegeixen del material de l'objecte al JSON de l'escena. **Necessites afegir informació al material?** Sí, hem creat una classe abstracta "ToonMaterial". Aquesta classe hereta de Material i alhora és la mare de tots els altres materials. En aquesta classe hem afegit l'atribut "gradientColor" que és un vector de colors. Hem hagut d'implementar els mètodes de llegir i escriure a fitxer. Aquestes funcions criden a les respectives funcions de Material, però a més llegeixen o escriuen el vector de tonalitats. 
    A part del Cel shading com a tal, hem implementat també les extensions explicades a classe, on hem incorporat la component especular, i la llum ambient. A més, hem afegit la silueta dels objectes, que surten ressaltats dins l'escena.
    Per admetre un nombre arbitrari d'intervals, per calcular el color en cada punt calculem $t = \lfloor n \cdot x \rfloor$ on x ès el cosinus entre l'angle de llum i la normal, i n el nombre d'intervals. Aleshores t és l'índex de l'interval corresponent. En cas que el cosinus sigui 1, hem decidit posar el color més clar del que disposem.
    
    * **Llum direccional**. Hem implementat una nova classe de llum, la direccional. Aquesta no té posició, doncs està situada a l'infinit. A més, la seva atenuació sempre és 1, pel mateix motiu. Té 2 atributs propis: intensitat i direcció.
    
### Screenshots de cada fase
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
   
   - Intersecció dels rajos amb una esfera
    
    <img src="screenshots/FASE_00/05_esfera_color_shading.png" alt="Color shading una esfera" width="300">
    <img src="screenshots/FASE_00/06_esfera_normal_shading.png" alt="Normal shading una esfera" width="300">
    <img src="" alt="Depth shading una esfera" width="300">
    
    - Intersecció dels rajos amb dues esferes
    
    <img src="screenshots/FASE_00/08_virtualscene_color_shading.png" alt="Color shading dues esferes" width="300">
    <img src="" alt="Depth shading dues esferes" width="300">


* **Fase 1**: 

* **Fase 2**:
    - Cel Shading i les seves ombres

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
    
    * **Pas 4: Afegir recursió al mètode RayPixel per a tindre en compte els rajos reflectits** 
        
        - Resultats obtinguts amb dues esferes amb material Lambertià, valors de Max Depth 1, 3 i 10 i nombre de samples 10. Shading Blinn-Phong, fitxer de setup setupRenderTwoSpheres.json i fitxer de dades twoSpheres.json
    
    <imgsrc="screenshots/FASE_02/RRR/RRR_01.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_02.png" alt="Amb Max Depth 3" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_03.png" alt="Amb Max Depth 10" width="300">
        
        - Resultats obtinguts al assignar la intensitat ambient global als rajos secundaris que no intersequen amb l'escena.
    
    <imgsrc="screenshots/FASE_02/RRR/RRR_04.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_05.png" alt="Amb Max Depth 10" width="300">
    
        - Resultats obtinguts al visualitzar dues esferes lambertianes i una de metàl.lica, amb valors de Max Depth 1, 3 i 10 i nombre de samples 10. Shading Blinn-Phong, fitxer de setup setupRenderSpheres.json i fitxer de dades threeSpheres.json
    
    <imgsrc="screenshots/FASE_02/RRR/RRR_06.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_07.png" alt="Amb Max Depth 3" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_08.png" alt="Amb Max Depth 10" width="300">
    
        - Visualitzacions dels shadings Phong, Cel i Normal amb mateix setup file i fitxer de dades.
            - Phong Shading:
            
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 3" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 10" width="300">
    
            - Cel Shading:
            
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 3" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 10" width="300">
            
            - Normal Shading:

    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 3" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_.png" alt="Amb Max Depth 10" width="300">
    
    * **Pas 5: Afegir recursió al mètode RayPixel per a tindre en compte objectes transparents**
        
        - **Tot i que el codi no està llegint la nu-t, on hauries de llegir-la?**
            A la classe Material, al mètode read() s'ha de llegir també el paràmetre nu-t; si el fitxer json conté el paràmetre nut i aquest valor és de tipus double, s'ha d'assignar el valor a la variable nu-t del material.
        
        - Resultats obtinguts al visualitzar el fitxer spheresMetalTransp.json i el setupRenderTwoSpheres.json. Max depth pren els valors 1, 2 i 3, i el nombre de samples és 10.
        
    <imgsrc="screenshots/FASE_02/RRR/RRR_9.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_10.png" alt="Amb Max Depth 2" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_11.png" alt="Amb Max Depth 3" width="300">
    
        - Modificant el punt de vista amb valors de lookFrom (-5, 0, 1) i lookAt (-2, 0, 0) i canviat el valor de kd a [0.7, 0.7, 0.7]
    
    <imgsrc="screenshots/FASE_02/RRR/RRR_12.png" alt="Amb Max Depth 3" width="300">
    
        - **Per què si tens el MAX_DEPTH a 1, l'esfera no es veu transparent?**
            Si tenim el valor MAX_DEPTH a 1, això significa que només es farà un rebot de llum, és a dir, només es seguirà un raig de llum després de xocar amb l'objecte. Per tant, si l'objecte és opac, no es veurà res més enllà d'aquest objecte, ja que només es considera un únic rebot de llum.
        
        - Visualitzacions amb el fitxer fourSpheres.json i el setupRenderFourSpheres.json i nivells de recursivitat MAXDEPTH = 1, 2, i 4. Nombre de samples és 10.
        
    <imgsrc="screenshots/FASE_02/RRR/RRR_13.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_14.png" alt="Amb Max Depth 2" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_15.png" alt="Amb Max Depth 4" width="300">
    
        - **Si assignes el color ambient global enlloc del de background en els rajos secundaris que no intersequen amb res. Com et canvia la visualització? Raona el per què?**
            Si assignem el color ambient global en lloc del color de fons (background) en els rajos secundaris que no intersequen amb cap objecte, la visualització canvia perquè tots els píxels que no estan directament en la línia de visió dels objectes de la nostra escena reben el mateix color ambient, creant una mena d'il·luminació uniforme en la imatge. Això pot ser útil per crear un efecte d'illuminació ambiental a la nostra escena, però també pot provocar que la imatge aparegui una mica "plana" i sense profunditat.
            
        - Visualització de l'escena anterior fent que els rajos secundaris que no intersequen amb l'escena rebin el color ambient global.
        
    <imgsrc="screenshots/FASE_02/RRR/RRR_16.png" alt="Amb Max Depth 1" width="300">
    
        - Visualització de l'escena anterior fent que no es ponderi el color local.
    
    <imgsrc="screenshots/FASE_02/RRR/RRR_17.png" alt="Amb Max Depth 1" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_18.png" alt="Amb Max Depth 2" width="300">
    <imgsrc="screenshots/FASE_02/RRR/RRR_19.png" alt="Amb Max Depth 4" width="300">
        
        - **Raona per què en aquests casos l'escena es veu més clara**
            Si no es pondera el color local amb (1- colorScattered) els materials transparents no absorveixen la llum que travessa l'objecte, cosa que significa que la llum passa per ells sense ser atenuada. Això pot fer que les escenes semblin més brillants i clares en general, però també afecta negativament en la percepció de la profunditat i oclusió de la imatge.
    
        
* **Fase 3**:
    - **Amb el fitxer de setup setupDataEuropa.json quina de les dues imatges obtens? Raona per què.**
    
      Ens trobem en la situació de la dreta: és fàcil de veure, si mirem dadesEuropa.json, trobem que el pla correspon a l'equació {y=-1}, i està afitat per valors d'x i z entre -50 i 50. Com que és un fitxer de tipus RealData, per les esferes en coneixem el valor x i z del centre, i li donem valor y = 0 per defecte al centre. A més, pel nostre escalat, l'esfera més gran tindrà radi = 1. Per tant, cap de les esferes travessarà el pla com es veu a la imatge 1. 
      
    - **Qui calcularà les coordenades (u, v) del punt d’intersecció amb el pla?**
    
      Les calcularà la classe fitted plane i les desarà a l'atribut uv de la classe HitInfo, perquè hi pugui accedir el shading corresponent.
      
    - **Quina de les dues visualitzacions obtens? **
    
      Obtenim la segona visualització:
      
      ![imagen](https://user-images.githubusercontent.com/80753129/227035406-78d659d9-ff69-4768-8ae6-e33469b71009.png "Visualització Fase 3 1.3")
      
    -  **Visualitzacions associades a dadesBCN_Zoom i dadesBCN**
    -  

    


* **Opcionals**:
    - Directional Light
    
    ![Captura de Pantalla 2023-03-20 a las 22 07 05](https://user-images.githubusercontent.com/69910092/226466772-27d20596-31ae-4b0b-ae55-39f110759f46.png "Directional Light (-1, -0.6, -0.3)") 
    
    ![Captura de Pantalla 2023-03-20 a las 22 09 24](https://user-images.githubusercontent.com/69910092/226466784-43696e94-f314-4e6f-b6ce-b553b32f6b78.png "Directional Light (1, -0.6, -0.3)")

    El groc clar que es veu "independentment d'on ve la llum" és el rim de la bola gran.
    

* **Més visualitzacions**:

   * Per totes les imatges, incluiu aqui la imatge obtinguda i els fitxers de dades i de configuració que heu fet servir
