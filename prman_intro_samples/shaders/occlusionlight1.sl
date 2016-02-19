light
occlusionlight1(
  float samples = 64;
  color filter = color(1);
  output float __nonspecular = 1;)
{
  normal Ns = normalize(N);

  illuminate (Ps + Ns) {  /* force execution independent of light location */

    /* Compute occlusion */
    float hits = 0;
    gather("illuminance", Ps, Ns, PI/2, samples,
           "distribution", "cosine") {
      hits += 1;
    }
    float occlusion = hits / samples;

    /* Set Cl */
    Cl = filter * (1 - occlusion);
  }
}