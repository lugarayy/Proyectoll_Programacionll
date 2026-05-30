# Proyecto Final - Simulación de Supervivencia Espacial

## Información General

**Universidad Nacional de Costa Rica**  
**Escuela de Informática**  
**Proyecto II - Programación II 2026**  
**Motor de Simulación de Aventuras y Mazmorras**

- Curso: EIF204 - Programación II
- Carrera: Ingeniería de Sistemas de Información
- Nivel: Segundo año
- Periodo lectivo: I Ciclo 2026
- Modalidad: Presencial
- Valor: 100 puntos
- Lenguaje: C++

---

# 1. Descripción general

El presente proyecto consiste en el desarrollo de un motor de simulación en consola para representar una aventura dentro de un mundo compuesto por espacios conectados, personajes, elementos interactivos, eventos y objetivos de progreso.

El sistema no tiene como finalidad construir un videojuego gráfico. Su propósito es modelar una simulación mediante objetos en C++, donde el estado del mundo cambia durante la ejecución y donde las acciones ocurridas puedan verificarse posteriormente mediante archivos de salida.

La ambientación, las reglas internas, el tipo de mundo, la forma de exploración y los elementos concretos de la aventura serán definidos por cada equipo.

---

# 2. Relación con el curso

Este proyecto integra contenidos fundamentales de Programación II:

- Diseño orientado a objetos
- Relaciones entre clases
- Herencia
- Polimorfismo
- Manejo de memoria
- Programación genérica
- Iteradores
- Sobrecarga de operadores
- Archivos
- Excepciones
- Patrones de diseño

---

# 3. Objetivo general

Diseñar e implementar en C++ un motor de simulación de aventuras capaz de cargar información inicial desde archivos de texto, construir una representación interna del mundo, ejecutar una simulación verificable, registrar los hechos relevantes y generar un reporte final.

---

# 4. Problema a resolver

Un personaje inicia una aventura en un mundo descrito mediante archivos de texto. El sistema debe construir una representación interna del escenario y ejecutar una simulación donde ocurran interacciones entre el personaje, el entorno y los demás elementos definidos por el equipo.

---

# 5. Alcance esperado

La solución deberá representar:

- Un mundo compuesto por espacios relacionados.
- Un personaje principal.
- Elementos interactivos.
- Amenazas, eventos u obstáculos.
- Algún tipo de progreso o misión.
- Registro de acontecimientos.
- Reporte final generado en archivo de texto.

---

# 6. Funcionamiento esperado

1. Cargar información desde archivos.
2. Construir el mundo interno.
3. Ejecutar la simulación.
4. Registrar eventos.
5. Generar archivos de salida.
6. Mostrar el resultado final.

---

# 7. Requerimientos no funcionales

- Código modular y mantenible.
- Bajo acoplamiento.
- Nombres de código en inglés.
- Comentarios internos en inglés.
- Documento técnico en español o inglés.
- Uso de rutas relativas.
- Manejo adecuado de errores.
- Ejecución reproducible.

---

# 8. Criterios de valoración técnica

Se valorará:

- Modelado orientado a objetos.
- Relaciones coherentes entre clases.
- Herencia y polimorfismo cuando sean necesarios.
- Manejo responsable de memoria.
- Programación genérica.
- Iteradores.
- Sobrecarga de operadores.
- Manejo de archivos y excepciones.
- Uso justificado de patrones de diseño.

---

# 9. Archivos de entrada y salida

## Entrada

- rooms.txt
- items.txt
- threats.txt

## Salida

- simulation.log
- final_report.txt

---

# 10. Entregables

## E1 - Código fuente completo

Proyecto completo en C++ que compile y ejecute sin errores.

## E2 - Archivos de entrada

Archivos de texto utilizados para cargar la aventura.

## E3 - Archivos de salida

Bitácora y reporte final generados por el programa.

## E4 - Documento técnico

Documento PDF con las principales decisiones de diseño e implementación.

## E5 - README.md

Instrucciones de compilación, ejecución y estructura del proyecto.

## E6 - Evidencia de ejecución

Capturas, salidas y archivos generados.

## E7 - Defensa técnica opcional

Explicación y justificación de la solución.

---

# 11. Contenido sugerido del documento técnico

- Descripción general del sistema.
- Temática de la aventura.
- Formato de archivos.
- Clases y relaciones.
- Decisiones de diseño.
- Manejo de memoria.
- Manejo de archivos y errores.
- Técnicas utilizadas.
- Evidencia de ejecución.
- Mejoras futuras.

---

# 12. Rúbrica de evaluación

| Criterio | Puntaje |
|-----------|----------|
| Simulación funcional | 25 pts |
| Diseño orientado a objetos | 20 pts |
| Criterio técnico | 20 pts |
| Archivos y manejo de errores | 15 pts |
| Documento técnico | 10 pts |
| Organización general | 10 pts |
| **Total** | **100 pts** |

---

# 13. Reglas de incumplimiento crítico

- El proyecto no compila.
- No existe simulación real.
- No se cargan datos desde archivos.
- Salida fija sin simulación.
- No se generan archivos de salida.
- No existe evidencia de ejecución.
- No se entrega el código fuente completo.

---

# 14. Condiciones de aceptación

- El proyecto debe compilar correctamente.
- Debe ejecutarse sin errores críticos.
- Deben entregarse todos los archivos necesarios.
- No se aceptan rutas absolutas.
- No se aceptan dependencias no autorizadas.

---

# 15. Criterio global de aprobación

El proyecto debe demostrar la capacidad del equipo para diseñar e implementar una solución orientada a objetos en C++ con comportamiento real, manejo adecuado de archivos, errores y decisiones de diseño.

---

# Cronograma de Desarrollo

## Semana 1 — 29 mayo al 4 junio

### Ambos juntos

- Definir formato de archivos `.txt` de entrada.
- Diagrama de clases final acordado.

### Persona A

- Clases `Room` y `Station`.
- Clase base `Item`.
- `OxygenTank`, `RepairKit`, `KeyCard`.
- `WorldLoader`.

### Persona B

- Clase abstracta `Entity`.
- Clase `Character`.
- Clase `Threat`.
- `DefectiveRobot` y `OxygenLeak`.
- `Logger` (Singleton).

---

## Semana 2 — 5 al 9 junio

### Persona A

- Factory para amenazas.
- Validaciones.
- Excepciones.
- Templates.
- Sobrecarga de `<<`.

### Persona B

- `SimulationEngine`.
- Eventos y combate.
- Iteradores.
- `ReportGenerator`.
- Sobrecarga de `==`.

### Ambos juntos

- Integración.
- Pruebas.

---

## 10 al 11 junio — Documentación y entrega

### Ambos juntos

- Documento técnico PDF.
- README.md.
- Evidencia de ejecución.
- Revisión final.
- Entrega.
