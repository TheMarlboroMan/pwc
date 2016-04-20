#include "principal.h"

#ifdef WINCOMPIL
/* Localización del parche mingw32... Esto debería estar en otro lado, supongo. */
#include <herramientas/herramientas/herramientas.h>
#endif

using namespace App;

Controlador_principal::Controlador_principal(DLibH::Log_base& log, const Herramientas_proyecto::Gestor_fuentes_TTF& f, const Localizador& l, Sistema_audio& sa)
	:log(log),
	localizador(l),
	sistema_audio(sa),
	fuente(f.obtener_fuente("akashi", 20))
{
}

void Controlador_principal::preloop(DFramework::Input& input, float delta)
{

}

void Controlador_principal::loop(DFramework::Input& input, float delta)
{
	if(input.es_senal_salida())
	{
		abandonar_aplicacion();
		return;
	}

	if(input.es_input_down(Input::arriba) ||
		input.es_input_down(Input::abajo) ||
		input.es_input_down(Input::izquierda) ||
		input.es_input_down(Input::derecha) ||
		input.es_input_down(Input::escape))
	{
		abandonar_aplicacion();
		return;
	}
}

void Controlador_principal::postloop(DFramework::Input& input, float delta)
{

}

void Controlador_principal::dibujar(DLibV::Pantalla& pantalla)
{
	pantalla.limpiar(0, 64, 0, 255);

	DLibV::Representacion_TTF ttf(fuente, {255, 255, 255, 255}, "LOL");
	ttf.ir_a(20, 20);
	ttf.volcar(pantalla);
}


void  Controlador_principal::despertar()
{

}

void  Controlador_principal::dormir()
{

}

bool Controlador_principal::es_posible_abandonar_estado() const
{
	return true;
}
