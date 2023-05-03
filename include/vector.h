#ifndef VECTOR_H
#define VECTOR_H


// https://github.com/etale-cohomology/miawm/blob/master/miawm_util.c


#define i64 long


#define VEC_IDIM_CAP_INI  0x100


#define m_min(       A, B)             ({  typeof(A) _a=(A);  typeof(B) _b=(B);  _a<_b ?  _a : _b;  })
#define m_max(       A, B)             ({  typeof(A) _a=(A);  typeof(B) _b=(B);  _a<_b ?  _b : _a;  })


#define vec__idim_set(    VEC, VAL)  (((i64*)(VEC))[-2] = (VAL))
#define vec__idim_cap_set(VEC, VAL)  (((i64*)(VEC))[-1] = (VAL))
#define vec_idim(         VEC)       (((i64*)(VEC))[-2])
#define vec_idim_cap(     VEC)       (((i64*)(VEC))[-1])
#define vec_bdim(         VEC)       (sizeof(*VEC) * vec_idim(VEC))
#define vec_bdim_cap(     VEC)       (sizeof(*VEC) * vec_idim_cap(VEC))


#define vec_init(VEC_TYPE_T)({                                                \
  i64* _base = malloc(2*sizeof(i64) + sizeof(VEC_TYPE_T)*VEC_IDIM_CAP_INI);  \
  vec__idim_set(    (void*)(&_base[2]), 0);                                  \
  vec__idim_cap_set((void*)(&_base[2]), VEC_IDIM_CAP_INI);                   \
  (void*)(&_base[2]);                                     \
})

#define vec_end(VEC)  do{           \
  i64* _base = &((i64*)(VEC))[-2];  \
  free(_base);                      \
}while(0)



#define vec_head(  VEC)              (VEC)
#define vec_tail(  VEC)              (&((VEC)[vec_idim(VEC)]))
#define vec_next(  VEC, IT)          (++(IT))
#define vec_forall(VEC, IT)          for(typeof(VEC) (IT) = vec_head((VEC));  (IT) != vec_tail((VEC));  vec_next((VEC),(IT)))


#define vec__resize(VEC, N)  do{                           \
  i64  _idim = (N);                                        \
  i64  _bdim = sizeof(i64)*2  + sizeof(*(VEC))*_idim;      \
  i64* _base = realloc(&((i64*)(VEC))[-2], _bdim);         \
  (VEC) = (void*)(&_base[2]);  /*We NEED this!*/           \
  vec__idim_set(    (VEC), m_min(vec_idim((VEC)),_idim));  \
  vec__idim_cap_set((VEC), _idim);                         \
}while(0)


#define vec_push(VEC, VAL)  do{         \
  i64 _idx      = vec_idim((VEC));      \
  i64 _idim_new = _idx+1;               \
  i64 _idim_cap = vec_idim_cap((VEC));  \
  if(_idim_cap < _idim_new){            \
    vec__resize((VEC), 2*_idim_cap+1);  \
  }                                     \
  vec__idim_set((VEC), _idim_new);      \
  (VEC)[_idx] = (VAL);                  \
}while(0)


#define vec_get(VEC, IDX)  ((VEC)[(IDX)])

#define vec_pop(VEC)  do{                         \
  i64 _idim_new = m_max(0, vec_idim((VEC)) - 1);  \
  vec__idim_set((VEC), _idim_new);                \
}while(0)


#define vec_del(VEC, IDX)  do{                    \
  i64 _idx      = (IDX);                          \
  i64 _idim_new = m_max(0, vec_idim((VEC)) - 1);  \
  if(0<=_idx && _idx<_idim_new+1){                \
    vec__idim_set((VEC), _idim_new);              \
    for(i64 _i=_idx; _i<_idim_new+1; ++_i){       \
      (VEC)[_i] = (VEC)[_i+1];                    \
    }                                             \
  }                                               \
}while(0)


#endif // VECTOR_H
