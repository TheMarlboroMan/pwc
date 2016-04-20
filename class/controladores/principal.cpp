#include "principal.h"

#include "../app/framework_impl/input.h"
#include <templates/parches_compat.h>

#include <class/tabla_animaciones.h>

#include "../app/recursos.h"

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

	Herramientas_proyecto::Tabla_sprites ts("data/graficos/sheet.dat");
	Herramientas_proyecto::Tabla_animaciones ta(ts, "data/graficos/animations.dat");

	DLibV::Representacion_TTF ttf(fuente, {255, 255, 255, 255}, "LOL"+compat::to_string(33) );
	ttf.ir_a(20, 20);
	ttf.volcar(pantalla);

	auto f=ta.obtener(3).obtener(0).frame;
	
	DLibV::Representacion_bitmap bmp(DLibV::Gestor_texturas::obtener(g_sprites));
	bmp.establecer_alpha(255);
	bmp.establecer_modo_blend(DLibV::Representacion::BLEND_ALPHA);
	bmp.establecer_mod_color(255, 255, 255);
	bmp.establecer_recorte(f.como_sdl_rect());
	bmp.establecer_posicion(100, 100, f.w, f.h);
	bmp.volcar(pantalla);
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
