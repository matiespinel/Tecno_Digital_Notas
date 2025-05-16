# Descomentar la siguiente línea si tenés Python versión 3.8.x o inferior (borrando el #).
# from __future__ import annotations

def nave_estelar_cercana(sensado: list[int], p: int) -> bool:
    """
    Requiere: **COMPLETAR**
    Devuelve: **COMPLETAR**
    """
    for nave in sensado:
        if nave <= p:
            return True
    return False
    # EJ 1: COMPLETAR

def naves_cercanas(sensado: list[int], p: int) -> list[int]:
    '''
    Requiere: **COMPLETAR**
    Devuelve: **COMPLETAR**
    '''
    naves_cercanas: list[int] = []
    # EJ 2: COMPLETAR
    for nave in sensado:
        if nave <= p:
            naves_cercanas.append(nave)
    return naves_cercanas
print (nave_estelar_cercana([1,2,3,500,234,456456,45646564,2], 1000))