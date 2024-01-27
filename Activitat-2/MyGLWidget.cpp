#include "MyGLWidget.h"

#include <iostream>

MyGLWidget::MyGLWidget (QWidget* parent) : QOpenGLWidget(parent), program(NULL)
{
  setFocusPolicy(Qt::StrongFocus);  // per rebre events de teclat
  xClick = yClick = 0;
  DoingInteractive = NONE;
}

MyGLWidget::~MyGLWidget ()
{
  if (program != NULL)
    delete program;
}

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();  
  glEnable(GL_DEPTH_TEST);
  
  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersModels();
  creaBuffersTerra();
  escenaMax = glm::vec3(7.5, 3.0, 5.0);
  escenaMin = glm::vec3(-7.5, 0.0, -5.0);
  iniEscena();
  iniCamera();
}

void MyGLWidget::iniEscena()
{
    radiEscena = distance(escenaMax, escenaMin) / 2.0;
    centreEscena = glm::vec3(0,0,0);
}

void MyGLWidget::iniCamera(){
  distancia = radiEscena * 2.0;
  fov = 2 * asin(radiEscena / distancia);
  znear = distancia - radiEscena;
  zfar = distancia + radiEscena;
  viewTransform();
  projectTransform();
}

void MyGLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Rick
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  
  //Morty alternatiu
  if(pintarMortyAlternatiu == 1){
      MortyAlternatiu = 1;
      glUniform1i(coloralternatiuLoc, MortyAlternatiu);
      glBindVertexArray (VAO_models[MORTY]);
      MortyTransform();
      glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
      MortyAlternatiu = 0;
      glUniform1i(coloralternatiuLoc, MortyAlternatiu);
  }

  // Portal
  glBindVertexArray (VAO_models[PORTAL]);
  PortalTransform();
  if(pintarPortal != 0) glDrawArrays(GL_TRIANGLES, 0, models[PORTAL].faces().size()*3);
  
  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  glBindVertexArray (0);
}

void MyGLWidget::RickTransform ()
{
  glm::mat4 TG(1.0f);  
  TG = glm::translate(TG, glm::vec3(-2.5f, 0, 0));
  TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
  TG = glm::rotate(TG, glm::radians(angleRick + 180.0f), glm::vec3(0, 1, 0));
  TG = glm::translate(TG, -centreBaseModels[RICK]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::MortyTransform ()
{
  glm::mat4 TG(1.0f);
  if(MortyAlternatiu == 0){
    TG = glm::translate(TG, posMorty);
    TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
    TG = glm::rotate(TG, glm::radians(angleMorty), glm::vec3(0, 1, 0));
  }else{
    TG = glm::translate(TG, posMortyPrePortal);
    TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
    TG = glm::rotate(TG, glm::radians(angleMortyPrePortal), glm::vec3(0, 1, 0));
  }
  TG = glm::translate(TG, -centreBaseModels[MORTY]);
  TGMorty = TG;
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::PortalTransform ()
{
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(-2.5f, 0 , 0));
  TG = glm::translate(TG, glm::vec3(sin(glm::radians(anglePortal)), 0, cos(glm::radians(anglePortal))) * glm::vec3(3));
  TG = glm::rotate(TG, glm::radians(anglePortal), glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(0.25f, 1 , 1));
  TG = glm::scale(TG, glm::vec3(escalaModels[PORTAL]));
  TG = glm::translate(TG, -centreBaseModels[PORTAL]);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::identTransform ()
{
  glm::mat4 TG(1.0f);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform ()
{
  glm::mat4 Proj(1.0f);
  Proj = glm::perspective (fov, ra, znear, zfar);
  glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]);
}

void MyGLWidget::viewTransform ()
{
  // Matriu de posició i orientació de l'observador
  glm::mat4 View(1.0f);
  if(POVMorty == 0){
      View = glm::translate(View, glm::vec3(0.0, 0.0, -distancia));
      View = glm::rotate(View, glm::radians(girTheta), glm::vec3(1.0, 0.0, 0.0));
      View = glm::rotate(View, -glm::radians(girPsi), glm::vec3(0.0, 1.0, 0.0));
      View = glm::translate(View, -centreEscena);
  }else{
      View = glm::lookAt(posMorty + glm::vec3(0, 0.8, 0), glm::vec3(100 * sin(glm::radians(angleMorty)), 0.8, 100 * cos(glm::radians(angleMorty))), glm::vec3(0, 1, 0)); //Arreglar
  }
  glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}


void MyGLWidget::resizeGL (int w, int h) 
{
// Aquest codi és necessari únicament per a MACs amb pantalla retina.
#ifdef __APPLE__
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif
  ra = float(ample)/float(alt);
  factorAngleY = M_PI / ample;
  factorAngleX = M_PI / alt;
  projectTransform();
}

bool MyGLWidget::MortyPortalTest(float angleRick, glm::vec3 posMorty)
{
  glm::vec3 posPortal = glm::vec3(sin(angleRick), 0.0, cos(angleRick)) * glm::vec3(3) + glm::vec3(-2.5,0,0);
  return (glm::distance(posMorty,posPortal) <= 0.2);
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) 
{
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { 
        posMorty = posMorty + glm::vec3(sin(glm::radians(angleMorty)), 0.0, cos(glm::radians(angleMorty))) * glm::vec3(0.1);
        if(MortyPortalTest(glm::radians(anglePortal), posMorty) && pintarPortal == 1){
            pintarPortal = 0;
            pintarMortyAlternatiu = 1;
            angleMortyPrePortal = angleMorty;
            posMortyPrePortal = posMorty;
        }
        viewTransform();
      break;
    }
    case Qt::Key_Down: {
        posMorty = posMorty - glm::vec3(sin(glm::radians(angleMorty)), 0.0, cos(glm::radians(angleMorty))) * glm::vec3(0.1);
        if(MortyPortalTest(glm::radians(anglePortal), posMorty) && pintarPortal == 1){
            pintarPortal = 0;
            pintarMortyAlternatiu = 1;
            angleMortyPrePortal = angleMorty;
            posMortyPrePortal = posMorty;
        }
        viewTransform();
       break;
    }
    case Qt::Key_Q: {
        angleRick += 45.0;
      break;
    }
    case Qt::Key_E: {
        angleRick -= 45.0;
      break;
    }
    case Qt::Key_P: {
        if(fmod(angleRick, 360.0) == fmod(anglePortal - 180.0, 360.0)){
            if(pintarPortal == 0){
                pintarPortal = 1;
            }else{
                pintarPortal = 0;
            }
        }else{
            anglePortal = angleRick + 180.0;
            pintarPortal = 1;
        }
      break;
    }
    case Qt::Key_Left: {
        angleMorty = angleMorty + 45.0;
        viewTransform();
        projectTransform();
       break;
    }
    case Qt::Key_Right: {
        angleMorty = angleMorty - 45.0;
        viewTransform();
        projectTransform();
       break;
    }
    case Qt::Key_C: {
        if(POVMorty == 0){
            POVMorty = 1;
            znear = 0.25;
            primeraPersona = true;
        }else{
            primeraPersona = false;
            POVMorty = 0;
            znear = distancia - radiEscena;
        }

        emit teclaC(primeraPersona);
        viewTransform();
        projectTransform();
       break;
    }
    case Qt::Key_R: {
        angleRick = angleMorty = girPsi= 0.0;
        xAnt = yAnt = POVMorty = pintarMortyAlternatiu = 0;
        pintarPortal = 1;
        anglePortal = 180.0;
        girTheta = 45.0;
        posMorty = glm::vec3(1, 0, 0);
        znear = distancia - radiEscena;
        primeraPersona = false;
        emit teclaC(primeraPersona);
        viewTransform();
        projectTransform();
       break;
    }
    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::mousePressEvent (QMouseEvent *e)
{
  xClick = e->x();
  yClick = e->y();

  if (e->button() & Qt::LeftButton &&
      ! (e->modifiers() & (Qt::ShiftModifier|Qt::AltModifier|Qt::ControlModifier)))
  {
    DoingInteractive = ROTATE;
  }
}

void MyGLWidget::mouseReleaseEvent( QMouseEvent *)
{
  DoingInteractive = NONE;
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  xClick = e->x();
  yClick = e->y();
  girPsi -= (xClick - xAnt) * factorAngleX;
  girTheta += (yClick - yAnt) * factorAngleY;
  xAnt = xClick;
  yAnt = yClick;
  viewTransform();
  update ();
}

void MyGLWidget::creaBuffersTerra ()
{
  // VBO amb la posició dels vèrtexs
  glm::vec3 posTerra[4] = {
        glm::vec3(-7.5, 0.0, -5.0),
        glm::vec3(-7.5, 0.0,  5.0),
        glm::vec3( 7.5, 0.0, -5.0),
        glm::vec3( 7.5, 0.0,  5.0)
  }; 

  glm::vec3 c(0.8, 0.7, 1.0);
  glm::vec3 colTerra[4] = { c, c, c, c };

  // VAO
  glGenVertexArrays(1, &VAO_Terra);
  glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);

  // geometria
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(posTerra), posTerra, GL_STATIC_DRAW);
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  // color
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colTerra), colTerra, GL_STATIC_DRAW);
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);
  
  glBindVertexArray (0);
}

void MyGLWidget::calculaCapsaModel (Model &p, float &escala, float alcadaDesitjada, glm::vec3 &centreBase)
{
  // Càlcul capsa contenidora i valors transformacions inicials
  float minx, miny, minz, maxx, maxy, maxz;
  minx = maxx = p.vertices()[0];
  miny = maxy = p.vertices()[1];
  minz = maxz = p.vertices()[2];
  for (unsigned int i = 3; i < p.vertices().size(); i+=3)
  {
    if (p.vertices()[i+0] < minx)
      minx = p.vertices()[i+0];
    if (p.vertices()[i+0] > maxx)
      maxx = p.vertices()[i+0];
    if (p.vertices()[i+1] < miny)
      miny = p.vertices()[i+1];
    if (p.vertices()[i+1] > maxy)
      maxy = p.vertices()[i+1];
    if (p.vertices()[i+2] < minz)
      minz = p.vertices()[i+2];
    if (p.vertices()[i+2] > maxz)
      maxz = p.vertices()[i+2];
  }
  escala = alcadaDesitjada/(maxy-miny);
  centreBase[0] = (minx+maxx)/2.0; centreBase[1] = miny; centreBase[2] = (minz+maxz)/2.0;
}

void MyGLWidget::creaBuffersModels ()
{
  // Càrrega dels models
  models[RICK].load("./models/Rick.obj");
  models[MORTY].load("./models/Morty.obj");
  models[PORTAL].load("./models/portal.obj");

  // Creació de VAOs i VBOs per pintar els models
  glGenVertexArrays(3, &VAO_models[0]);
  
  float alcadaDesitjada[3] = {2,1,3};
  
  for (int i = 0; i < 3; i++)
  {	
	  // Calculem la capsa contenidora del model
	  calculaCapsaModel (models[i], escalaModels[i], alcadaDesitjada[i], centreBaseModels[i]);
  
	  glBindVertexArray(VAO_models[i]);

	  GLuint VBO[2];
	  glGenBuffers(2, VBO);

	  // geometria
	  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*models[i].faces().size()*3*3,
		   models[i].VBO_vertices(), GL_STATIC_DRAW);
	  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	  glEnableVertexAttribArray(vertexLoc);

	  // color
	  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*models[i].faces().size()*3*3,
		   models[i].VBO_matdiff(), GL_STATIC_DRAW);
	  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	  glEnableVertexAttribArray(colorLoc);  
  }
  
  glBindVertexArray (0);
}

void MyGLWidget::carregaShaders()
{
  // Creem els shaders per al fragment shader i el vertex shader
  QOpenGLShader fs (QOpenGLShader::Fragment, this);
  QOpenGLShader vs (QOpenGLShader::Vertex, this);
  // Carreguem el codi dels fitxers i els compilem
  fs.compileSourceFile("shaders/basicShader.frag");
  vs.compileSourceFile("shaders/basicShader.vert");
  // Creem el program
  program = new QOpenGLShaderProgram(this);
  // Li afegim els shaders corresponents
  program->addShader(&fs);
  program->addShader(&vs);
  // Linkem el program
  program->link();
  // Indiquem que aquest és el program que volem usar
  program->bind();

  // Identificador per als  atributs
  vertexLoc = glGetAttribLocation (program->programId(), "vertex");
  colorLoc = glGetAttribLocation (program->programId(), "color");

  // Identificadors dels uniform locations
  transLoc = glGetUniformLocation(program->programId(), "TG");
  projLoc  = glGetUniformLocation (program->programId(), "Proj");
  viewLoc  = glGetUniformLocation (program->programId(), "View");
  coloralternatiuLoc = glGetUniformLocation (program->programId(), "Alternatiu");
}

void MyGLWidget::canviacamera(int value){
    makeCurrent();
    POVMorty = value;
    if(POVMorty == 1){
        znear = 0.25;
    }else{
        znear = distancia - radiEscena;
    }
    viewTransform();
    projectTransform();
    update();
}



