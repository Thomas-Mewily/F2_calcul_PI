#include "__base__.hpp"

fmax simPi(umax nbPoint)
{
    umax nbInside = 0;
    repeat(_, nbPoint)
    {
        fmax x = mt_real();
        fmax y = mt_real();
        if(x*x+y*y <= 1)
        {
            nbInside++;
        }
    }
    return ((double)nbInside*4.0)/nbPoint;
}

void question_simPi()
{
    umax nbLance = 1;
    repeat(i, 9)
    {
        printf("simPi(%12" umax_format") = %9.7" fmax_format "\n", nbLance, simPi(nbLance));
        nbLance *= 10;
    }
    printf("\n");
}

void question_simPi_moyennee()
{
    umax nbLance = 1000;
    umax nbRepetition = 10;
    repeat(i, 3)
    {
        // Copied from the C version of <math.h> because I'm in C++ and not C, there is no M_PI in <math.h> in C++
        #define M_PI       3.14159265358979323846

        fmax moyenne = 0;
        repeat(i, nbRepetition)
        {
            moyenne += simPi(nbLance);
        }   
        moyenne /= nbRepetition;
        printf("moyenne(somme(%2" umax_format ", simPi(%12" umax_format "))) = %9.7" fmax_format, nbRepetition, nbLance, moyenne);
        printf(" , différence absolue avec M_PI : %9.7" fmax_format "\n", fabs(moyenne-M_PI));
        nbLance *= 1000;
    }
    printf("\n");
}

fmax simPi_interval_confiance(umax nbLance, umax nbExperience, fmax t_coef)
{
    umax n = nbExperience;

    fmax* pis = make_array(fmax, n);
    fmax moyenne = 0;

    repeat(i, n)
    {
        fmax pi = simPi(nbLance);

        pis[i] = pi;
        moyenne += pi / n;
    }

    fmax s2 = 0;
    repeat(i, n)
    {
        s2 += squared(pis[i] - moyenne);
    }
    s2 /= (n-1);

    fmax r = t_coef * sqrt(s2/n);

    free(pis);

    printf("simPi_interval_confiance(%12" umax_format " lancés, %3" umax_format " repetitions n, %9.7" fmax_format " t_coef) => pi= %9.7" fmax_format " +/- %9.7" fmax_format "\n", nbLance, nbExperience, t_coef, moyenne, r);
    return r;
}

void question_simPi_interval_confiance()
{
    umax nbLance = 10000000;
    simPi_interval_confiance(nbLance, 1,  12.706);
    simPi_interval_confiance(nbLance, 2,  4.303);
    simPi_interval_confiance(nbLance, 10, 2.228);
    simPi_interval_confiance(nbLance, 20, 2.086);
    simPi_interval_confiance(nbLance, 30, 2.042);
    //simPi_interval_confiance(nbLance, 40, 2.021);
    printf("\n");
}

void latex()
{
    //for(usize i = 1; i < 10000; i*=2)
    /*
    for(usize i = 1; i < 1000; i+=1)
    {
        printf("(%" usize_format ", %" fmax_format ")\n", i, simPi(i));
    }*/

    file* f = fopen("test.txt", "w+");
    check(f != null);

    distribution d = distribution(3, 4, 0.0001);
    latex_file_figure_begin(f, "nombre de lancé", "approximation de pi");
    umax nbSimulation = 100000;
    #define nbLance 10000

    repeat(i, nbSimulation)
    {
        fmax pi = simPi(nbLance);
        d.inc(pi);
    }

    latex_file_figure_plot_begin(f);
    d.fprint_latex_data(f);
    latex_file_figure_plot_end(f);
    latex_file_figure_end(f, nbSimulation, "moyenne de PI (" to_string(nbLance) " points)");
    #undef nbLance

    fclose(f);
}

fmax simPiDroite(umax nbPoint, fmax coefApetit)
{
    // developpement limité
    fmax X = 1-coefApetit*coefApetit/2;
    fmax Xend = 1-X;

    umax nbInside = 0;
    repeat(i, nbPoint)
    {
        fmax x;
        fmax y;
        do
        {
            x = mt_real()*Xend+X;
            y = mt_real();
        } while(y > coefApetit*x);
        if(x*x+y*y <= 1)
        {
            nbInside++;
        }
    }

    fmax Ymiddle = X*coefApetit;
    fmax aire_g = X*Ymiddle/2;
    fmax aire_d = (Ymiddle+ coefApetit)/2*Xend;
    return  4*(90/coefApetit)*(aire_g+aire_d*((fmax)aire_d*nbInside)/nbPoint);
}

int main(int argc, char const* argv[])
{
    unused(argc);
    unused(argv);

    only_in_debug(printf("%sCompiled%s at %s \n", COLOR_DEBUG_CATEGORY, COLOR_RESET, current_time));
    only_in_debug(betterCPP_verification());
    print_size(fmax);

    u32 init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    mt_init_by_array(init, length);

    //latex();

    question_simPi();
    question_simPi_interval_confiance();
    question_simPi_moyennee(); // à la fin car ça prends pas mal de temps
    
    only_in_debug(memory_printf_final());
    only_in_release(printf("fin\n"));
    return EXIT_SUCCESS;
}

/*
https://perso.isima.fr/~dahill/Simu-ZZ2/Lab%20%23%203%20-%20Simu%20PI%20&%20Conf%20Intervals%20ann%c3%a9e%20impaire.pdf
*/