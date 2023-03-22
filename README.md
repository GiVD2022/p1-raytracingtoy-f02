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
  -Fase 2
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
    
* **Fase 3**:
    - Amb el fitxer de setup setupDataEuropa.json quina de les dues imatges obtens? Raona per què.
      Ens trobem en la situació de la dreta: és fàcil de veure, si mirem dadesEuropa.json, trobem que el pla correspon a l'equació {y=-1}, i està afitat per valors d'x i z entre -50 i 50. Com que és un fitxer de tipus RealData, per les esferes en coneixem el valor x i z del centre, i li donem valor y = 0 per defecte al centre. A més, pel nostre escalat, l'esfera més gran tindrà radi = 1. Per tant, cap de les esferes travessarà el pla com es veu a la imatge 1. 
* **Opcionals**:
    - Directional Light
    
    ![Captura de Pantalla 2023-03-20 a las 22 07 05](https://user-images.githubusercontent.com/69910092/226466772-27d20596-31ae-4b0b-ae55-39f110759f46.png "Directional Light (-1, -0.6, -0.3)") 
    
    ![Captura de Pantalla 2023-03-20 a las 22 09 24](https://user-images.githubusercontent.com/69910092/226466784-43696e94-f314-4e6f-b6ce-b553b32f6b78.png "Directional Light (1, -0.6, -0.3)")

    El groc clar que es veu "independentment d'on ve la llum" és el rim de la bola gran.
    

* **Més visualitzacions**:

   * Per totes les imatges, incluiu aqui la imatge obtinguda i els fitxers de dades i de configuració que heu fet servir
