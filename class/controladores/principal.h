#ifndef CONTROLADOR_PRINCIPAL_H
#define CONTROLADOR_PRINCIPAL_H

//Dependencias...
#include "estados_controladores.h"
#include "../framework/controlador_interface.h"


//Específicos de la aplicación...
#include <class/gestor_fuentes_ttf.h>
#include "../app/localizador.h"
#include "../app/sistema_audio.h"


namespace App
{

class Controlador_principal:
	public DFramework::Controlador_interface
{
	public:

						Controlador_principal(DLibH::Log_base&, const Herramientas_proyecto::Gestor_fuentes_TTF&, const Localizador&, Sistema_audio&);

	virtual void 				preloop(DFramework::Input& input, float delta);
	virtual void 				loop(DFramework::Input& input, float delta);
	virtual void 				postloop(DFramework::Input& input, float delta);
	virtual void 				dibujar(DLibV::Pantalla& pantalla);
	virtual void 				despertar();
	virtual void 				dormir();
	virtual bool				es_posible_abandonar_estado() const;

	private:
	
	DLibH::Log_base&			log;
	const Localizador&			localizador;
	Sistema_audio&				sistema_audio;
	const DLibV::Fuente_TTF&		fuente;
};

}

#endif
