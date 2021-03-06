## PID Project Write up

__

The goals / steps of this project are the following:

* Build PID controller to control car autonomously around the track
* Tune PID hyperparameters by applying process flow previously described


__

## Implementation

I designed two PID controllers which were allocated to control cross track error (CTE) and speed.

The CTE controller uses the steering angle command as the actuator to minimize the CTE.

The speed controller uses the throttle command as the actuator to target the desired speed.

Both controllers used the same class and function definition to update the error and initialize the hyperparameters as follows:

```C
  void PID::Init(double Kp, double Ki, double Kd) {
  	Kp_ = Kp;
  	Ki_ = Ki;
  	Kd_ = Kd;
  	prev_error = 0.0;
  }
```
```C
  void PID::UpdateError(double cte) {
  	p_error = Kp_*cte;
  	i_error += Ki_*cte;
  	i_error = clip(i_error,-0.5*Kp_,0.5*Kp_); // clip integrator to avoid windup issues
  	double diff_error = prev_error-cte;
  	d_error = Kd_*diff_error;
  	prev_error = cte;
```

I decided to clip the integrator component in order to avoid integrator windup issues.

__

## Reflection

* Describe the effect of each PID component

The P, or "proportional", term uses a gain that's proportional to the error that you are trying to minimize or control (CTE or speed). This most observable effect is the controller trying to put in opposite or correction command to the error seen.

The D, or "differential", term uses a gain on the differential error from the previous time step to the current time step. The most observable effect here is the controller trying to counter large changes in error by reducing the amount of command used. This assists in overshooting and stopping the controller from oscillating around the command.

The I, or "integral", term uses a gain on the integrated error from all previous time steps. This removes steady state bias error and the most observable effect is that at low frequency the error will slowly converge to 0.

The vehicle behaved as expected when each component was removed and added as part of the solution.

The following PID parameters were used in the CTE controller:

| Hyper Parameter        | Value   |
|:-------------:|:-------------:|
| Proportional      |   0.2      |
| Integral     |   0.001    |
| Derivative    |  -0.4     |

The CTE's sign has to flipped in order to incorporate negative feedback for the control system. The parameters were hand tuned by selecting the P gain first and finding a reasonably stable looking system. After that, the D term was used to try to add damping to the system. Finally, the I term was added to minimize the steady state error.

The following parameters were used to tune the speed controller.


|Hyper Parameter | Value   |
|:-------------:|:-------------:|
| Proportional      |   1.0      |
| Integral     |   0.01    |

The parameters were tuned by verifying the desired speed tracking throughout the simulation. The P term was selected to be large to converge on the speed error and the I term was used again to minimize steady state error.
