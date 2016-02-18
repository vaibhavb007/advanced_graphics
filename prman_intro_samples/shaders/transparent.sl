surface
transparent
(
    float Ka=.1,
          Ks=.1,
          Kd=.1,
          Kr=.1,
          Kt=.9,
          roughness=.1,
          eta=0.75;
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
    vector refracted_ray = refract(In, v, eta);
    Ci += Cs * Kt * trace(P, refracted_ray);
  }

  color local_illumination = Ka * ambient() + Kd * diffuse(Nn) + Ks * specular(v, -In, roughness);

  Ci += Cs * local_illumination;
  Ci *= Os;
  Oi = Os;
}
