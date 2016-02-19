surface
metal
(
    float Ka=0.4,
          Ks=0.6,
          Kd=0.5,
          Kr=0.8,
          Kt=0,
          roughness=.1,
          eta=1.33;
    color specularcolor=1
)
{
  normal Nn = normalize(N);
  vector In = normalize(I);

  uniform float d = 0;
  rayinfo("depth", d);

  normal v = faceforward(Nn, In);
  v = normalize(v);
  if (d < 5) {
    if (Nn.In < 0) {
      vector reflected_ray = reflect(In,Nn);
      Ci += Cs * Kr * trace(P, reflected_ray);
    }
  }

  color local_illumination = Ka * ambient() + Kd * diffuse(Nn) + Ks * specular(v, -In, roughness);

  Ci += Cs * local_illumination;
  Ci *= Os;
  Oi = Os;
}