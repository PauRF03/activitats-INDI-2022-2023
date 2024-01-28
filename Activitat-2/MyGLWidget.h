#define GLM_FORCE_RADIANS
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
	Q_OBJECT
	public:
		MyGLWidget (QWidget *parent=0);
		~MyGLWidget ();
	public slots:
		void canviacamera(int value); //Slot amb un valor que indica quin dels dos butons de la interfície s'ha apretat.
	signals:
		void teclaC(bool primeraP); //Signal que s'emet quan es canvia la càmera amb la tecla C, amb un booleà que indica si és la de primera persona o no.
	protected:
		// initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
		virtual void initializeGL ( );
		// paintGL - Mètode cridat cada cop que cal refrescar la finestra.
		// Tot el que es dibuixa es dibuixa aqui.
		virtual void paintGL ( );
		// resizeGL - És cridat quan canvia la mida del widget
		virtual void resizeGL (int width, int height);
		// keyPressEvent - Es cridat quan es prem una tecla
		virtual void keyPressEvent (QKeyEvent *event);
		// mouse{Press/Release/Move}Event - Són cridades quan es realitza l'event
		// corresponent de ratolí
		virtual void mousePressEvent (QMouseEvent *event);
		virtual void mouseReleaseEvent (QMouseEvent *event);
		virtual void mouseMoveEvent (QMouseEvent *event);

	private:
		// iniEscena - Aqui incluim les inicialitzacions de l'escena
		void iniEscena ();
		// iniCamera - Aqui incluim les inicialitzacions de la camera
		void iniCamera ();    
		// creaBuffersModels - Aquí carreguem els fitxers obj i fem la 
		// inicialització dels diferents VAOS i VBOs
		void creaBuffersModels ();
		// creaBuffersTerra - Aqui inicialitzem el VAO i els VBO d'un model 
		// fet a mà que representa un terra
		void creaBuffersTerra ();
		// carregaShaders - Aquí carreguem els shaders, els compilem i els 
		// linkem. També busquem els uniform locations que fem servir.
		void carregaShaders ();
		    
		// viewTransform i projecTransform - Es fan servir per a construir 
		// i enviar als shader les matrius de càmera (View i Projection 
		// respectivament).
		virtual void viewTransform ();
		virtual void projectTransform ();
		    
		// {Rick/Morty/Portal/ident}Transform - Funciones per construir i 
		// enviar al shader diferents matrius de transformació geomètrica TG
		virtual void RickTransform();
		virtual void MortyTransform();
		virtual void PortalTransform();
		virtual void identTransform();
		   
		// calculaCapsaModel - Calcula la capsa contenidora d'un Model p 
		// retornant el centre de la seva base a CentreBase, i el factor
		// d'escala necessari per a que la seva alçada sigui 
		// alcadaDesitjada.
		virtual void calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &CentreBase);
		  
		// MortyPortalTest - Mètode que es pot fer servir per veure si el 
		// Morty està molt a prop del Portal (només comprova distàncies 
		// entre posMorty i la posició portal calculada a partir de l'angle 
		// que té en Rick quan obre el portal angleRick).
		virtual bool MortyPortalTest(float angleRick, glm::vec3 posMorty);

		// attribute locations
		GLuint vertexLoc, colorLoc;

		// uniform locations
		GLuint transLoc, viewLoc, projLoc;

		// enum models - els models estan en un array de VAOs (VAO_models), aquest enum és per fer més llegible el codi. 
		typedef enum { RICK = 0, MORTY = 1, PORTAL = 2} ModelType;

		// VAO names
		GLuint VAO_models[3];
		GLuint VAO_Terra;

		// Program
		QOpenGLShaderProgram *program;

		// Viewport
		GLint ample, alt;

		// Mouse interaction
		typedef  enum {NONE, ROTATE} InteractiveAction;
		InteractiveAction DoingInteractive;
		int xClick, yClick;
		int xAnt = 0;
		int yAnt = 0;
		int POVMorty = 0; //Variable que indica quina càmera s'està utilitzant
		float factorAngleX, factorAngleY;

		// Internal vars
		float radiEscena, distancia;
		float fov, ra, znear, zfar;
		float girPsi = 0.0;
		float girTheta = 45.0;
		glm::vec3 centreEscena, obs, vrp, up;

		// Models, capses contenidores i escales
		Model models[3];
		glm::vec3 centreBaseModels[3];        
		float escalaModels[3];
		    
		// Guardem la TG del Morty original per si la necessitem més tard
		glm::mat4 TGMorty;
		  
		// Orientació i posició del Morty original
		float angleMorty = 0.0;
		glm::vec3 posMorty = glm::vec3(1,0,0);
		    
		//Orientació del Rick
		float angleRick = 0.0;

		// Variable per guardar la TG pel Morty d'un univers alternatiu    
		glm::mat4 TGMorty2;

		//Variables per guardar el màxim i el mínim de l'escena
		glm::vec3 escenaMax, escenaMin;

		//Variables per fer aparèixer portals
		float anglePortal = 180.0;
		int pintarPortal = 1;

		//Variables per fer aparèixer un Morty d'un univers alternatiu
		glm::vec3 posMortyPrePortal;
		int pintarMortyAlternatiu = 0;
		GLuint MortyAlternatiu = 0;
		float angleMortyPrePortal = 0.0;
		GLuint coloralternatiuLoc;
		bool primeraPersona = false;
};
