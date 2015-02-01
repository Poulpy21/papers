/*        Generated by TAPENADE     (INRIA, Tropics team)
    Tapenade 3.10 (r5485M) - 15 Jan 2015 10:00
*/
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3_s;

/*
  Differentiation of f in reverse (adjoint) mode:
   gradient     of useful results: f.x f.y f.z
   with respect to varying inputs: u.x u.y u.z
*/
void f_b(Vec3_s u, Vec3_s *ub, Vec3_s fb) {
    Vec3_s v;
    Vec3_s vb;
    Vec3_s f;
    vb = fb;
    ub->x = (28.0f-u.z)*vb.y - 10.0f*vb.x + u.y*vb.z;
    ub->y = 10.0f*vb.x - vb.y + u.x*vb.z;
    ub->z = -(u.x*vb.y) - 8.0f*vb.z/3.0f;
}

/*
  Differentiation of RK4_step in reverse (adjoint) mode:
   gradient     of useful results: dt RK4_step.x RK4_step.y RK4_step.z
   with respect to varying inputs: dt
   RW status of diff variables: dt:incr RK4_step.x:in-killed RK4_step.y:in-killed
                RK4_step.z:in-killed
*/
void RK4_step_b(Vec3_s u_k, float dt, float *dtb, Vec3_s RK4_stepb) {
    Vec3_s k1, k2, k3, k4;
    Vec3_s k2b, k3b, k4b;
    Vec3_s y2, y3, y4;
    Vec3_s y2b, y3b, y4b;
    Vec3_s v_k;
    Vec3_s v_kb;
    Vec3_s RK4_step;
    float tempb1;
    float tempb0;
    float tempb;
    k1 = f(u_k);
    y2.x = u_k.x + k1.x*dt/2.0f;
    y2.y = u_k.y + k1.y*dt/2.0f;
    y2.z = u_k.z + k1.z*dt/2.0f;
    k2 = f(y2);
    y3.x = u_k.x + k2.x*dt/2.0f;
    y3.y = u_k.y + k2.y*dt/2.0f;
    y3.z = u_k.z + k2.z*dt/2.0f;
    k3 = f(y3);
    y4.x = u_k.x + k3.x*dt;
    y4.y = u_k.y + k3.y*dt;
    y4.z = u_k.z + k3.z*dt;
    k4 = f(y4);
    v_kb = RK4_stepb;
    tempb = dt*v_kb.z/6.0f;
    k4b.z = tempb;
    tempb0 = dt*v_kb.y/6.0f;
    k4b.y = tempb0;
    tempb1 = dt*v_kb.x/6.0f;
    k4b.x = tempb1;
    f_b(y4, &y4b, k4b);
    k3b.z = dt*y4b.z + 2*tempb;
    k3b.y = dt*y4b.y + 2*tempb0;
    k3b.x = dt*y4b.x + 2*tempb1;
    f_b(y3, &y3b, k3b);
    k2b.z = dt*y3b.z/2.0f + 2*tempb;
    k2b.y = dt*y3b.y/2.0f + 2*tempb0;
    k2b.x = dt*y3b.x/2.0f + 2*tempb1;
    f_b(y2, &y2b, k2b);
    *dtb = *dtb + (k1.y+2*k2.y+2*k3.y+k4.y)*v_kb.y/6.0f + k3.z*y4b.z + k3.x*
        y4b.x + k2.y*y3b.y/2.0f + k1.z*y2b.z/2.0f + k1.x*y2b.x/2.0f + k1.y*y2b
        .y/2.0f + k2.x*y3b.x/2.0f + k2.z*y3b.z/2.0f + k3.y*y4b.y + (k1.x+2*k2.
        x+2*k3.x+k4.x)*v_kb.x/6.0f + (k1.z+2*k2.z+2*k3.z+k4.z)*v_kb.z/6.0f;
}