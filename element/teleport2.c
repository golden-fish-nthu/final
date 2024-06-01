#include "teleport.h"
#include <stdbool.h>
/*
   [teleport function]
*/
Elements *New_Teleport2(int label)
{
    Teleport2 *pDerivedObj = (Teleport2 *)malloc(sizeof(Teleport2));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/teleport.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = WIDTH - pDerivedObj->width;
    pDerivedObj->y = HEIGHT - pDerivedObj->height;
    pDerivedObj->activate = false;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Teleport2_update;
    pObj->Interact = Teleport2_interact;
    pObj->Draw = Teleport2_draw;
    pObj->Destroy = Teleport2_destory;
    return pObj;
}
void Teleport2_update(Elements *self)
{
    Teleport2 *Obj = ((Teleport2 *)(self->pDerivedObj));
    if (key_state[ALLEGRO_KEY_W])
    {
        Obj->activate = true;
    }
    else
    {
        Obj->activate = false;
    }
}
void Teleport2_interact(Elements *self, Elements *tar)
{
    if (tar->label == Character_L)
    {
        Character *chara = (Character *)(tar->pDerivedObj);
        Teleport2 *Obj = (Teleport2 *)(self->pDerivedObj);
        if (chara->x >= Obj->x &&
            chara->x <= Obj->x + Obj->width &&
            Obj->activate)
        {
            _Character_update_position(tar, 0 - chara->x, 0);
        }
    }
}
void Teleport2_draw(Elements *self)
{
    Teleport2 *Obj = ((Teleport2 *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Teleport2_destory(Elements *self)
{
    Teleport2 *Obj = ((Teleport2 *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(self);
}
