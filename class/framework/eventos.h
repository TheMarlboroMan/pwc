#ifndef FRAMEWORK_EVENTOS_H
#define FRAMEWORK_EVENTOS_H

#include <vector>
#include <memory>

namespace DFramework
{

/**
* Un sistema de mensajería (no necesariamente eventos, pero es un buen nombre)
* para que los diferentes controladores puedan comunicarse con una central,
* que sería el bootstrap de la aplicación.
* De momento no hay nada pensado para que diferentes controladores se 
* comuniquen entre si fuera del código que ya tenemos en el bootstrap. Siempre
* sería posible añadir una cola de mensajes que pueda consumirse entre los
* propios controladores. 
*/

//F-f-f-f-forward :D!.
class Interprete_eventos_interface;

/**
* Base para un evento. Un evento es una estructura que tendrá sus propios 
* valores indicando lo que sea que haya ocurrido. Incluye un método virtual
* para indicar su tipo de evento de acuerdo con un entero. Es tarea del 
* intérprete "desmontar" cada evento para convertirlo en el tipo deseado.
*/

struct Evento_framework_interface
{
	virtual	int		tipo_evento() const=0;
};


/**
* Esto es la clase base para un interprete de eventos. La idea es que el 
* intérprete sea completamente opcional para la aplicación y que tenga estado.
* Por ejemplo, podría tener una referencia a la configuración para poder
* actualizar los valores de configuración en respuesta a eventos que vayan
* llegando.
*/

class Interprete_eventos_interface
{
	public:

	virtual void		interpretar_evento(const Evento_framework_interface& ev)=0;
};

typedef std::unique_ptr<Evento_framework_interface> uptr_evento;

/**
* La cola de eventos es una clase separada que contiene el vector. Será propiedad
* del director de estados pero se inyectará en los controladores al registrarlos.
*/

class Cola_eventos
{
	public:

	size_t			size() const {return cola_eventos.size();}

	//Encola un evento para ser procesado al final del loop actual.
	void			encolar_evento(uptr_evento& ev)
	{
		cola_eventos.push_back(std::move(ev));
	}

	//Envia un evento que será interpretado inmediatamente.
	void			enviar_evento(uptr_evento& ev)
	{
		interprete->interpretar_evento(*ev);
	}

	//Realiza el proceso de la cola de eventos... La idea es que esto lo llame sólo el director de estados.
	void			procesar_cola_completa(Interprete_eventos_interface& i)
	{
		for(auto& ev : cola_eventos) i.interpretar_evento(*ev);
		cola_eventos.clear();
	}

	//Establece un intérprete de eventos para el "enviar eventos". Lo hace el director al registrar el intérprete.
	void			establecer_interprete(Interprete_eventos_interface& e)
	{
		interprete=&e;
	}

	private:

	std::vector<std::unique_ptr<Evento_framework_interface>>	cola_eventos;
	Interprete_eventos_interface *					interprete;
	
};

}
#endif
