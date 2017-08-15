#ifndef SPM_VEHICLE_DYNAMIC
#define SPM_VEHICLE_DYNAMIC

/*

Musings on how to compute the car speed at time step i.

By and large, we want the car to say on the track (no spin), do not exceed the
maximum possible speed or accelerate faster than the engine can push and do not
decelerate faster than the brakes can stop it.

Assume that the braking and accelerating power is not influenced by the cornering (in real life, 
tires can make that much friction force: if you use it to break, ther won't be enough left to turn the car, and it spins).

This mean the "pilot" has to keep it at a speed that is the minimum of:
 - geometry speed -> how fast you can go without spinning (depends on the geometry of the corners)
 - engine speed -> how fast can the engine push it against air and tire resistance
 - braking speed -> how fast you can afford to go now, knowing that you have to slow down later on.

Geometry speed depends on centripetal forces (assuming a flat, horizontal track).

    Fa = mu * ((g * m)  + d)

with
    - Fa the friction that you can have between tires and track
    - mu friction coefficient (0.6 to 1.1 http://www.hwupgrade.it/forum/archive/index.php/t-900763.html)
    - g the usual 8.81 m/s^2
    - m the mass of the car at that moment (account for fuel usage)
    - d the downforce.

The downdforce depends on the speed itself. We discount this aspect by using the speed at the previous timestep
to compute it (otherwise we have to deal with differential equations).

Pose the above equal to the centripetal force, with r the curvature radius of the track and V the speed we are looking for:
          m V^2
    Fc = ------
            r

Then solve in V.

The engine speed should be solvable via "teorema delle forze vive". The kinetic energy "now" is the energy before
minus the work of friction plus the engine power added in the time step. Roughly, it should be:

    Ec = Eb + P * dt - W

with
    - Ec the energy now
    - Eb the energy before
    - P the maximum engine power
    - dt the time step of the simulation
    - W the energy bled by air and tires's resistance.

Once Ec and the car mass are known, just compute the velocity. If it is smaller than the geometry-limited velocity,
it means that the limit is not the engine power: actually the pilot is using less than full throttle.

W again depends on the speed itself (linearly below 30km/h and with the 3rd power after as per
https://it.wikipedia.org/wiki/Potenza_(fisica)#Relazione_con_la_velocit.C3.A0_in_autoveicoli).

Now, the breaks. This is complicated, as it depends on the speed that must be attained at a future point in the 
track. The car must start to break "ahead" or it won't make it slow enough at the critical point.
This is very, very complicated to solve properly (especially if there is downforce involved, as that makes
the braking power and maximum corner speed depend on the speed itself).

I use a "reverse acceleration" approach and do not account for downforce when breaking.
Scan the track for the proverbial "3 corners ahead", say 500 meters.
Find the point with the slowest cornering speed. Assume the car is there at that speed, racing backward with air resistance as
a "positive" force. Check the speed it reaches at the point the car actually is.
That speed must not be exceeded, or it won't break in time.

The problem with downforce is that it raises the cornering speed by an unknown amount
(we would have to imagine how much downforce is available at the minimum speed point to compute the
actual allowed speed).

Since the braking part makes the computation much harder, I do not account for it. Infinite brakes are possible.
It will be interesting to record the braking levels and see if they ever touch absurd limits.

Pilot behavior will be accounted for probabilistiacally. Depending on pilot skill, the car may be
declared "too fast" or "too slow" without any relation to the physics of the situation. Throttle response
is ignored as well and assumed to be instantaneous.

I am wondering if I can aproximate the above by using Bezier curves to "graph" the situation.
A curve for the engine, starting at current speed, ending at a precomputed max speed with proper tangents.
A braking curve, tangent to the corner speed curve and ending on the critical point...
*/


namespace spm {

    /** Helper to deal with "human-readable" measurement units. 
        May have to be moved to the "mechanical car" class, where we deal with horsepower. */
    float horsepowerToWatts(const float horsepower);
    float wattsToHorsepower(const float watts);

    // TODO: Km/h to m/s - 1m/s = 3.6 Km/h

    /** Some place to put all the fixed elements of the car that influence the simulation.
        We are talking about engine power, fuel load, empty mass, downforce generation...
        
        It also hosts the dynamic part (the speed), but not the travelled distance, because geometry
        (positions) is accounted in another class.
        
        Most of the content of this class is constant. But that would force to have a constructor with a lot
        of parameters, so I break the rules here for ease of coding. This is also why the variables are listed
        before the methods.

        All the measures are in the SI (so meters, kilograms, seconds, newtons...).

        TODO: some of the thing may depend on pilot settings (e. g. use more fuel to get more power).
        Some of this values may migrate elsewhere as the model improves.

        TODO: account (somewhere else) for mechanical damage (crashes, worn out parts, outright bad luck...).
        TODO: somehow account for brake condition (maybe as an influence on the pilot settings, or breakdown frequency).
        TODO: account for fuel consumption, tire degradation, engine overheating (or general fatigue).
        TODO: allow the car to come to an halt (e. g. pit stops).
        TODO: allow (elsewhere) the car to go slwer intentionally (yellow flags).
    */
    class DynamicCar {
    public:

        /* How sticky the tires are. Depends on the quality and the formulation of the rubber. 
           Not adjusted for wet track or heating - that is not part of the car.  */
        float tireBaseFrictionCoefficient;
         
        /** Expressed in N/s. Depends on the engine and component quality.
            Assumed constant at any speed (e. g. discount for air ram scoop, 
            power curve etc). */
        float maximumEnginePower;
        
        /** How "penetrating" the car is. Depends on the quality of the aero parts and the flap settings.
            Assume all cars have the same frontal section when accounting for aerodinamics.
            Should be around 0.3, from memory. */
        float airResistanceCoefficient;

        /** Ratio between speed and downforce. Depends on the quality of aero parts and the flap settings.
            Assumed constant at any speed. Downforce is assumed to be quadratic with speed. */
        float downforceCoefficient;

        /** How much the car weights, including the pilot. Depends on chassis, components and how fat the driver is. */
        float dryWeight;

        /** How fast the car is going. */
        float speed;
        
        /** Entry point to do everything the car model has to do. */
        void timeStep(const float deltaT, const float trajectoryCurvatureRadius);


    private:
        float computeAirResistance() const;
    } ;

}

#endif