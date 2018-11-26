package de.novensa.cs.performance.macadamia.management.jvm;

import de.novensa.cs.performance.macadamia.management.jvm.resources.AbstractCrucialJvmResources;
import de.novensa.cs.performance.macadamia.management.jvm.resources.JvmResourceDetails;

import javax.annotation.Nullable;
import java.util.concurrent.TimeUnit;

/**
 * This class finds out what resource is to what extend precious and therefore provides hints if the implementation
 * can reach the target in a different approach. An example may be using <code>Radix-Sort</code> when CPU time is
 * crucial and <code>Collections.sort</code> or <code>Arrays.sort</code> (both merge sort) when memory is crucial to
 * a higher extend.
 *
 * @author Daniel Schulz
 */
public class UniformDistributedCrucialJvmResources extends AbstractCrucialJvmResources {


    @Override
    public void scheduleUpdates() {
        this.add(new JvmResourceDetails());
    }


    // constructor
    public UniformDistributedCrucialJvmResources(long initDelay, long period, @Nullable TimeUnit timeUnit) {
        super(initDelay, period, timeUnit);
    }
}
